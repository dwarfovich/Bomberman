#ifndef SERVER_HPP
#define SERVER_HPP

#include "game/game_object.hpp"
#include "messages/message.hpp"
#include "messages/i_message_visitor.hpp"

#include <QTcpServer>

#include <vector>
#include <unordered_set>

namespace bm {
class ServerWorker;
class Message;
class TextMessage;
class ClientNameMessage;

inline const quint16 defaultPort   = 44100;
inline const uint8_t wrongClientId = 0xFF;

class Server : public QTcpServer, public IMessageVisitor
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);

    void visit(const TextMessage& message) override;
    void visit(const ClientNameMessage& message) override;

    void          setServerPort(quint16 port);
    void          startListen();
    void          startListen(const QHostAddress& address, quint16 port);
    uint8_t       clients() const;
    void          sendMessage(const Message& message, ServerWorker* excludeClient);
    void          broadcastMessage(const Message& message, ServerWorker* excludeClient = nullptr);
    ServerWorker* currentMessageClient() const;

signals:
    void messageReceived(const std::unique_ptr<Message>& message);
    void logMessageRequest(const QString& message);
    void clientConnected(uint8_t clientId, QString name);
    void clientNameChanged(uint8_t clientId, QString name);

protected:
    void incomingConnection(qintptr descriptor) override;

private slots:
    void onMessageReceived(bm::ServerWorker* client, const std::unique_ptr<Message>& message);
    void onUserDisconnected(bm::ServerWorker* client);

private: // data
    std::vector<ServerWorker*> clients_;
    ServerWorker*              currentMessageClient_ = nullptr;
};

} // namespace bm

#endif // SERVER_HPP
