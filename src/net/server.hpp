#ifndef SERVER_HPP
#define SERVER_HPP

#include "message.hpp"

#include <QTcpServer>

#include <vector>

namespace bm {
class ServerWorker;
class Message;

inline const quint16 defaultPort = 44100;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);

    void setServerPort(quint16 port);
    void startListen();
    void startListen(const QHostAddress& address, quint16 port);

signals:
    void logMessageRequest(const QString& message);
    void clientConnected();

protected:
    void incomingConnection(qintptr descriptor) override;

private slots:
    void messageReceived(bm::ServerWorker* client, const std::unique_ptr<Message>& message);
    void onUserDisconnected(bm::ServerWorker* client);

private:
    std::vector<ServerWorker*> clients_;
};

} // namespace bm

#endif // SERVER_HPP
