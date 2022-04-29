#include "server.hpp"
#include "server_worker.hpp"
#include "messages/message.hpp"
#include "messages/text_message.hpp"
#include "messages/client_name_message.hpp"
#include "messages/set_player_id_message.hpp"
#include "messages/player_ready_message.hpp"
#include "messages/client_joining_game_message.hpp"

namespace bm {

// TODO: implement client disconnection.
Server::Server(QObject *parent) : QTcpServer { parent }
{
}

void Server::visit(const TextMessage &message)
{
    emit logMessageRequest(currentMessageClient_->clientName() + ": " + message.payload());
}

void Server::visit(const ClientNameMessage &message)
{
    const auto &name = message.payload();
    currentMessageClient_->setClientName(name);
    emit clientNameChanged(currentMessageClient_->clientId(), name);
}

void Server::setServerPort(quint16 port)
{
    const auto &address = serverAddress();
    listen(address, port);
}

void Server::startListen()
{
    startListen(serverAddress(), serverPort());
}

void Server::startListen(const QHostAddress &address, quint16 port)
{
    auto success = listen(address, port);
    if (success) {
        emit logMessageRequest("Listen started at " + serverAddress().toString() + ':' + QString::number(serverPort()));
    } else {
        emit logMessageRequest("Cannot start listen at " + serverAddress().toString() + ':'
                               + QString::number(serverPort()));
    }
}

uint8_t Server::clients() const
{
    return clients_.size();
}

void Server::sendMessage(const Message &message, ServerWorker *excludeClient)
{
    excludeClient->sendMessage(message);
}

void Server::incomingConnection(qintptr descriptor)
{
    ServerWorker *client = new ServerWorker { this };
    if (!client->isValid()) {
        emit logMessageRequest("Cann't connect client: out of clients ids");
        client->deleteLater();
        return;
    }

    if (!client->setSocketDescriptor(descriptor)) {
        emit logMessageRequest("Cannot set socket descriptor");
        client->deleteLater();
        return;
    }

    connect(client, &ServerWorker::clientDisconnected, this, std::bind(&Server::onUserDisconnected, this, client));

    connect(client,
            &ServerWorker::messageReceived,
            this,
            std::bind(&Server::onMessageReceived, this, client, std::placeholders::_1));

    clients_.push_back(client);
    currentMessageClient_ = client;
    emit clientConnected(client->clientId(), client->clientName());
    emit logMessageRequest("New client connected");
}

void Server::onMessageReceived(ServerWorker *client, const std::unique_ptr<Message> &message)
{
    currentMessageClient_ = client;
    message->accept(*this);
    emit messageReceived(message);
}

// TODO: Implement.
void Server::onUserDisconnected(ServerWorker *client)
{
    emit clientDisconnected(client->clientId());
}

ServerWorker *Server::currentMessageClient() const
{
    return currentMessageClient_;
}

void Server::broadcastMessage(const Message &message, ServerWorker *excludeClient)
{
    for (auto *client : clients_) {
        if (client != excludeClient) {
            client->sendMessage(message);
        }
    }
}

void Server::visit(const ClientJoiningGameMessage &message)
{
    emit clientJoinedGame(currentMessageClient_->clientId());
}

} // namespace bm
