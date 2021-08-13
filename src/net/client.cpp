#include "client.hpp"
#include "text_message.hpp"
#include "client_name_message.hpp"
#include "message_factory.hpp"
#include "text_message.hpp"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>

namespace bm {

Client::Client(QObject *parent) : QObject { parent }, socket_ { new QTcpSocket { this } }
{
    connect(socket_, &QTcpSocket::connected, this, &Client::onConnectedToServer);
    connect(socket_, &QTcpSocket::disconnected, this, [this]() {
        emit logMessage("Disconnected from server");
    });
    connect(socket_, &QTcpSocket::errorOccurred, this, &Client::onSocketError);
    connect(socket_, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::connectToServer(const QHostAddress &address, quint16 port)
{
    socket_->connectToHost(address, port, QIODevice::ReadWrite);
}

void Client::disconnect()
{}

void Client::sendMessage(const Message &message)
{
    QDataStream stream { socket_ };
    stream << message;
}

void Client::onSocketError(QAbstractSocket::SocketError error)
{
    emit logMessage("Socket error: " + socket_->errorString());
}

void Client::onReadyRead()
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
                //                emit messageReceived(std::move(currentMessage_));
                currentMessage_->accept(*this);
                currentStage_ = MessageReadingStage::Header;
            } else {
                canReadMessage = false;
            }
        }
}

void Client::sendPlayerNameMessage()
{
    ClientNameMessage nameMessage { name_ };
    sendMessage(nameMessage);
}

const QString &Client::name() const
{
    return name_;
}

void Client::setName(const QString &newName)
{
    name_ = newName;
    sendPlayerNameMessage();
}

void Client::onConnectedToServer()
{
    emit logMessage("Connected successfully");
    sendPlayerNameMessage();
}

void Client::visit(const TextMessage &message)
{
    emit logMessage(message.toString());
}

} // namespace bm
