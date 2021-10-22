#include "server_worker.hpp"
#include "socket.hpp"
#include "messages/message_type.hpp"
#include "messages/message.hpp"
#include "messages/message_factory.hpp"

#include <QDataStream>

#include <stdexcept>

namespace bm {

uint8_t              ServerWorker::nextClientId_ = 0;
std::vector<uint8_t> ServerWorker::freedIds      = {};

ServerWorker::ServerWorker(QObject *parent) : QObject { parent }, socket_ { new Socket { this } }
{
    clientId_ = nextId();
    connect(socket_, &Socket::messageReceived, this, &ServerWorker::messageReceived);
}

ServerWorker::~ServerWorker()
{
    socket_->disconnectFromHost();
    freedIds.push_back(clientId_);
}

bool ServerWorker::isValid() const
{
    return (clientId_ != invalidClientId);
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

uint8_t ServerWorker::clientId() const
{
    return clientId_;
}

uint8_t ServerWorker::nextId()
{
    auto nextId = invalidClientId;
    if (!freedIds.empty()) {
        nextId = freedIds.back();
        freedIds.pop_back();
    } else {
        if (nextClientId_ != invalidClientId) {
            nextId = nextClientId_++;
        }
    }

    return nextId;
}

} // namespace bm
