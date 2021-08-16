#include "server.hpp"
#include "server_worker.hpp"
#include "message.hpp"
#include "text_message.hpp"
#include "client_name_message.hpp"

namespace bm {

Server::Server(QObject *parent) : QTcpServer { parent }
{}

void Server::visit(const TextMessage &message)
{
    emit logMessageRequest(currentMessageClient_->clientName() + ": " + message.toString());
}

void Server::visit(const ClientNameMessage &message)
{
    currentMessageClient_->setClientName(message.toString());
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

void Server::incomingConnection(qintptr descriptor)
{
    auto *worker = new ServerWorker(this);
    if (!worker->setSocketDescriptor(descriptor)) {
        emit logMessageRequest("Cannot set socket descriptor");
        worker->deleteLater();
        return;
    }

    connect(worker, &ServerWorker::clientDisconnected, this, std::bind(&Server::onUserDisconnected, this, worker));

    connect(worker,
            &ServerWorker::messageReceived,
            this,
            std::bind(&Server::onMessageReceived, this, worker, std::placeholders::_1));
    // connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));

    // connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    clients_.push_back(worker);
    emit clientConnected();
    emit logMessageRequest("New client connected");
}

void Server::onMessageReceived(ServerWorker *client, const std::unique_ptr<Message> &message)
{
    currentMessageClient_ = client;
    message->accept(*this);
    emit messageReceived(message);
}

void Server::onUserDisconnected(ServerWorker *client)
{}

void Server::broadcastMessage(const Message &message, ServerWorker *excludeClient)
{
    for (auto *client : clients_) {
        if (client != excludeClient) {
            client->sendMessage(message);
        }
    }
}

} // namespace bm
