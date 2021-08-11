#include "client.hpp"
#include "text_message.hpp"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>

namespace bm {

Client::Client(QObject *parent) : QObject { parent }, socket_ { new QTcpSocket { this } }
{
    connect(socket_, &QTcpSocket::connected, this, [this]() {
        emit logMessage("Connected successfully");
    });
    connect(socket_, &QTcpSocket::disconnected, this, [this]() {
        emit logMessage("Disconnected from server");
    });
    connect(socket_, &QTcpSocket::errorOccurred, this, &Client::onSocketError);
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

} // namespace bm
