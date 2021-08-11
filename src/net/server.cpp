#include "server.hpp"
#include "server_worker.hpp"
#include "message.hpp"
#include "text_message.hpp"

namespace bm {

Server::Server(QObject *parent) : QTcpServer { parent }
{}

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
            std::bind(&Server::messageReceived, this, worker, std::placeholders::_1));
    // connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));

    // connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    clients_.push_back(worker);
    emit clientConnected();
    emit logMessageRequest("New client connected");
}

void Server::messageReceived(ServerWorker *client, const std::unique_ptr<Message> &message)
{
    if (message->type() == MessageType::Text) {
        auto textMessage = dynamic_cast<TextMessage *>(message.get());
        emit logMessageRequest(textMessage->toString());
    }
}

void Server::onUserDisconnected(ServerWorker *client)
{}

} // namespace bm
