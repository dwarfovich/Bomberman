#include "server.hpp"
#include "server_worker.hpp"
#include "messages/message.hpp"
#include "messages/text_message.hpp"
#include "messages/client_name_message.hpp"
#include "messages/set_player_id_message.hpp"
#include "messages/player_ready_message.hpp"

namespace bm {

Server::Server(QObject *parent) : QTcpServer { parent }
{}

void Server::visit(const TextMessage &message)
{
    emit logMessageRequest(currentMessageClient_->clientName() + ": " + message.toString());
}

void Server::visit(const ClientNameMessage &message)
{
    const auto &name = message.toString();
    currentMessageClient_->setClientName(message.toString());
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
    auto *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(descriptor)) {
        emit logMessageRequest("Cannot set socket descriptor");
        worker->deleteLater();
        return;
    }

    auto newId = generateClientId();
    if (newId == wrongClientId) {
        emit logMessageRequest("Connection rejected: out of client's ids");
        worker->deleteLater();
        return;
    }
    worker->setClientId(newId);

    connect(worker, &ServerWorker::clientDisconnected, this, std::bind(&Server::onUserDisconnected, this, worker));

    connect(worker,
            &ServerWorker::messageReceived,
            this,
            std::bind(&Server::onMessageReceived, this, worker, std::placeholders::_1));

    clients_.push_back(worker);
    emit clientConnected(newId, "New player");
    emit logMessageRequest("New client connected");

    SetPlayerIdMessage message { newId };
    worker->sendMessage(message);
}

void Server::onMessageReceived(ServerWorker *client, const std::unique_ptr<Message> &message)
{
    currentMessageClient_ = client;
    message->accept(*this);
    // TODO: Check if emitting this signal is neccessary.
    emit messageReceived(message);
}

void Server::onUserDisconnected(ServerWorker *client)
{}

uint8_t Server::generateClientId() const
{
    for (uint8_t i = serverId + 1; i < wrongClientId; ++i) {
        bool idUsed = false;
        for (const auto &client : clients_) {
            if (client->clientId() == i) {
                idUsed = true;
                break;
            }
        }
        if (!idUsed) {
            return i;
        }
    }

    return wrongClientId;
}

ServerWorker *Server::currentMessageClient() const
{
    return currentMessageClient_;
}

void Server::broadcastMessage(const Message &message, ServerWorker *excludeClient)
{
    if (message.type() == MessageType::MapInitialization) {
        emit logMessageRequest("Broadcasting MapInitialization message: " + QString::number(message.dataLength())
                               + " bytes");
    }
    for (auto *client : clients_) {
        if (client != excludeClient) {
            client->sendMessage(message);
        }
    }
}

const std::unordered_set<uint8_t> &Server::playersIds() const
{
    return playersReadyToStartGame_;
}

void Server::visit(const ClientJoiningGameMessage &message)
{
    //    playersReadyToStartGame_.insert(message.playerId());
    //    if (playersReadyToStartGame_.size() == clients_.size() + 1) {
    //        emit allClientsWaitingForGameData();
    //    }
}

void Server::visit(const PlayerReadyMessage &message)
{
    // TODO: Refactor.
    playersWithInitializedMap_.insert(playersWithInitializedMap_.size());
    if (playersWithInitializedMap_.size() == playersReadyToStartGame_.size()) {
        emit reallyReadyToStartGame();
    }
}
} // namespace bm
