#ifndef SERVER_HPP
#define SERVER_HPP

#include "message.hpp"
#include "i_message_visitor.hpp"

#include <QTcpServer>

#include <vector>

namespace bm {
class ServerWorker;
class Message;
class TextMessage;
class ClientNameMessage;

inline const quint16 defaultPort = 44100;

class Server : public QTcpServer, public IMessageVisitor
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);

    void visit(const TextMessage& message) override;
    void visit(const ClientNameMessage& message) override;
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
    void broadcastMessage(const Message& message, ServerWorker* excludeClient);

private:
    std::vector<ServerWorker*> clients_;
    ServerWorker*              currentMessageClient_ = nullptr;
};

} // namespace bm

#endif // SERVER_HPP
