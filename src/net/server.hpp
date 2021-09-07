#ifndef SERVER_HPP
#define SERVER_HPP

#include "message.hpp"
#include "i_message_visitor.hpp"

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
inline const uint8_t serverId      = 0;

class Server : public QTcpServer, public IMessageVisitor
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);

    void                               visit(const TextMessage& message) override;
    void                               visit(const ClientNameMessage& message) override;
    void                               setServerPort(quint16 port);
    void                               startListen();
    void                               startListen(const QHostAddress& address, quint16 port);
    uint8_t                            clients() const;
    void                               broadcastMessage(const Message& message, ServerWorker* excludeClient = nullptr);
    const std::unordered_set<uint8_t>& playersIds() const;

signals:
    void messageReceived(const std::unique_ptr<Message>& message);
    void logMessageRequest(const QString& message);
    void clientConnected(uint8_t clientId, QString name);
    void clientNameChanged(uint8_t clientId, QString name);
    // TODO: Rename signals.
    void allClientsWaitingForGameData();
    void reallyReadyToStartGame();

protected:
    void incomingConnection(qintptr descriptor) override;

private slots:
    void onMessageReceived(bm::ServerWorker* client, const std::unique_ptr<Message>& message);
    void onUserDisconnected(bm::ServerWorker* client);

private: // methods
    uint8_t generateClientId() const;

private: // data
    std::vector<ServerWorker*>  clients_;
    ServerWorker*               currentMessageClient_      = nullptr;
    std::unordered_set<uint8_t> playersReadyToStartGame_   = { serverId };
    std::unordered_set<uint8_t> playersWithInitializedMap_ = { serverId };

    // IMessageVisitor interface
public:
    void visit(const ClientReadyMessage& message) override;

    // IMessageVisitor interface
public:
    void          visit(const MapInitializedMessage& message) override;
    ServerWorker* currentMessageClient() const;
};

} // namespace bm

#endif // SERVER_HPP
