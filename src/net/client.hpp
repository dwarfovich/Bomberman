#ifndef BM_CLIENT_HPP
#define BM_CLIENT_HPP

#include "message.hpp"

#include <QObject>
#include <QAbstractSocket>

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QHostAddress;
QT_END_NAMESPACE

namespace bm {
class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject* parent = nullptr);

    void connectToServer(const QHostAddress& address, quint16 port);
    void disconnect();
    void sendMessage(const Message& message);

signals:
    void logMessage(const QString& message);

private slots:
    void onSocketError(QAbstractSocket::SocketError error);

private:
    QTcpSocket* socket_;
};

} // namespace bm

#endif // BM_CLIENT_HPP
