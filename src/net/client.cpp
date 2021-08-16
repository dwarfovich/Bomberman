#include "client.hpp"
#include "socket.hpp"
#include "text_message.hpp"
#include "client_name_message.hpp"
#include "message_factory.hpp"
#include "text_message.hpp"

#include <QHostAddress>
#include <QDataStream>

namespace bm {

Client::Client(QObject *parent) : QObject { parent }, socket_ { new Socket { this } }
{
    connect(socket_, &Socket::connected, this, &Client::onConnectedToServer);
    connect(socket_, &Socket::disconnected, this, [this]() {
        emit logMessage("Disconnected from server");
    });
    connect(socket_, &Socket::messageReceived, this, &Client::onMessageReceived);
    connect(socket_, &Socket::socketError, this, &Client::onSocketError);
}

void Client::connectToServer(const QHostAddress &address, quint16 port)
{
    socket_->connectToHost(address, port);
}

void Client::disconnect()
{
    socket_->disconnectFromHost();
}

void Client::sendMessage(const Message &message)
{
    socket_->sendMessage(message);
}

void Client::onSocketError(QAbstractSocket::SocketError error)
{
    emit logMessage("Socket error: " + socket_->errorString());
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

void Client::onMessageReceived(const std::unique_ptr<Message> &message)
{}

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
