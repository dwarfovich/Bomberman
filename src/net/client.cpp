#include "client.hpp"
#include "socket.hpp"
#include "text_message.hpp"
#include "client_name_message.hpp"
#include "message_factory.hpp"
#include "text_message.hpp"
#include "client_id_message.hpp"
#include "map_initialization_message.hpp"
#include "map_initialized_message.hpp"
#include "game/map.hpp"

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
    connect(socket_, &Socket::messageReceived, this, &Client::messageReceived);
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
    if (socket_->isConnected()) {
        ClientNameMessage nameMessage { name_ };
        sendMessage(nameMessage);
    }
}

const std::shared_ptr<Map> &Client::initializedMap() const
{
    return initializedMap_;
}

uint8_t Client::id() const
{
    return id_;
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
{
    message->accept(*this);
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

void Client::visit(const PrepareToStartGame &message)
{
    emit readyForPreparingToGameStart();
}

void Client::visit(const ClientIdMessage &message)
{
    id_ = message.playerId();
}

void Client::visit(const MapInitializationMessage &message)
{
    initializedMap_ = std::make_shared<Map>();
    QDataStream stream(message.data());
    stream >> *initializedMap_;

    auto                  bots = initializedMap_->bots();
    MapInitializedMessage mapInitializedMessage;
    sendMessage(mapInitializedMessage);
    emit readyToStartGame();
}

} // namespace bm
