#include "server_worker.hpp"
#include "socket.hpp"
#include "message_type.hpp"
#include "message.hpp"
#include "message_factory.hpp"

#include <QDataStream>

namespace bm {

ServerWorker::ServerWorker(QObject *parent) : QObject { parent }, socket_ { new Socket { this } }
{
    connect(socket_, &Socket::messageReceived, this, &ServerWorker::messageReceived);
}

ServerWorker::~ServerWorker()
{
    socket_->disconnectFromHost();
}

bool ServerWorker::setSocketDescriptor(qintptr descriptor)
{
    return socket_->setSocketDescriptor(descriptor);
}

const QString &ServerWorker::clientName() const
{
    return clientName_;
}

void ServerWorker::setClientName(const QString &newClientName)
{
    clientName_ = newClientName;
}

void ServerWorker::sendMessage(const Message &message)
{
    socket_->sendMessage(message);
}

} // namespace bm
