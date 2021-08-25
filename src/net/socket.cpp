#include "socket.hpp"
#include "message_factory.hpp"

#include <QTcpSocket>
#include <QDataStream>

namespace bm {

Socket::Socket(QObject *parent) : QObject { parent }, socket_ { new QTcpSocket { this } }
{
    connect(socket_, &QTcpSocket::connected, this, &Socket::connected);
    connect(socket_, &QTcpSocket::disconnected, this, &Socket::disconnected);
    connect(socket_, &QTcpSocket::errorOccurred, this, &Socket::socketError);
    connect(socket_, &QTcpSocket::readyRead, this, &Socket::onReadyRead);
}

bool Socket::isConnected() const
{
    return socket_->isOpen();
}

bool Socket::setSocketDescriptor(qintptr descriptor)
{
    return socket_->setSocketDescriptor(descriptor);
}

void Socket::connectToHost(const QHostAddress &address, quint16 port)
{
    socket_->connectToHost(address, port, QIODevice::ReadWrite);
}

void Socket::disconnectFromHost()
{
    socket_->disconnectFromHost();
}

void Socket::sendMessage(const Message &message)
{
    QDataStream stream { socket_ };
    stream << message;
}

QString Socket::errorString()
{
    return socket_->errorString();
}

void Socket::onReadyRead()
{
    QDataStream stream { socket_ };
    bool        canReadMessage = true;
    while (canReadMessage) {
        if (currentStage_ == MessageReadingStage::Header) {
            if (socket_->bytesAvailable() >= messageHeaderSize) {
                readHeader(stream);
            } else {
                canReadMessage = false;
            }
        } else { // MessageReadingStage::Data
            auto typ   = currentMessage_->type();
            auto ava   = socket_->bytesAvailable();
            auto expec = currentMessageSize_;
            if (socket_->bytesAvailable() >= currentMessageSize_) {
                readData(stream);
            } else {
                canReadMessage = false;
            }
        }
    }
}

void Socket::readHeader(QDataStream &stream)
{
    assert(!currentMessage_);

    MessageType type;
    stream >> type;
    currentMessage_ = MessageFactory::get().createMessage(type);
    stream >> currentMessageSize_;
    currentStage_ = MessageReadingStage::Data;
}

void Socket::readData(QDataStream &stream)
{
    Q_ASSERT(currentMessage_);
    stream >> *currentMessage_;
    emit messageReceived(currentMessage_);
    currentMessage_ = nullptr;
    currentStage_   = MessageReadingStage::Header;
}

} // namespace bm
