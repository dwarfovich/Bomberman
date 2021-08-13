#include "server_worker.hpp"
#include "message_type.hpp"
#include "message.hpp"
#include "message_factory.hpp"

#include <QTcpSocket>
#include <QDataStream>

namespace bm {

ServerWorker::ServerWorker(QObject *parent) : QObject { parent }, socket_ { new QTcpSocket { this } }
{
    connect(socket_, &QTcpSocket::readyRead, this, &ServerWorker::onReadyRead);
}

ServerWorker::~ServerWorker()
{
    socket_->disconnect();
}

bool ServerWorker::setSocketDescriptor(qintptr descriptor)
{
    return socket_->setSocketDescriptor(descriptor);
}

void ServerWorker::onReadyRead()
{
    // qDebug() << "On ready read: " << socket_->bytesAvailable() << " bytes";
    QDataStream stream { socket_ };
    bool        canReadMessage = true;
    while (canReadMessage)
        if (currentStage_ == MessageReadingStage::Header) {
            if (socket_->bytesAvailable() >= messageHeaderSize) {
                MessageType type;
                stream >> type;
                currentMessage_ = MessageFactory::get().createMessage(type);
                stream >> currentMessageSize_;
                // qDebug() << "Current message size:" << currentMessageSize_;
                currentStage_ = MessageReadingStage::Data;
            } else {
                canReadMessage = false;
            }
        } else { // MessageReadingStage::Data
            // qDebug() << "Comparing" << socket_->bytesAvailable() << currentMessageSize_;
            if (socket_->bytesAvailable() >= currentMessageSize_) {
                Q_ASSERT(currentMessage_);
                stream >> *currentMessage_;
                // qDebug() << "Message received:" << (int)currentMessage_->type();
                emit messageReceived(std::move(currentMessage_));
                currentStage_ = MessageReadingStage::Header;
            } else {
                canReadMessage = false;
            }
        }
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
    QDataStream stream { socket_ };
    stream << message;
}

} // namespace bm
