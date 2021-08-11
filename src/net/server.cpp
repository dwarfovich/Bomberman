#include "server.hpp"

#include "server_worker.hpp"

namespace bm {

Server::Server(QObject *parent) : QTcpServer { parent }
{
    // hello
}

void Server::setServerPort(quint16 port)
{
    const auto &address = serverAddress();
    listen(address, port);
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
    //    connect(worker,
    //            &ServerWorker::messageReceived,
    //            this,
    //            std::bind(&ChatServer::onMessageReceived, this, worker, std::placeholders::_1));
    // connect(worker, &ServerWorker::error, this, std::bind(&ChatServer::userError, this, worker));

    // connect(worker, &ServerWorker::logMessage, this, &ChatServer::logMessage);
    clients_.push_back(worker);
    emit clientConnected();
    emit logMessageRequest("New client connected");
}

void Server::onUserDisconnected(ServerWorker *client)
{}

} // namespace bm
