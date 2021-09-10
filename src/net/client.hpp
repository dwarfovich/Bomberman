#ifndef BM_CLIENT_HPP
#define BM_CLIENT_HPP

#include "messages/message.hpp"
#include "messages/i_message_visitor.hpp"
#include "game/game_object.hpp"

#include <QObject>
#include <QAbstractSocket>

QT_BEGIN_NAMESPACE
class QHostAddress;
QT_END_NAMESPACE

namespace bm {
class Socket;
class Map;

class Client : public QObject, public IMessageVisitor
{
    Q_OBJECT
public:
    explicit Client(QObject* parent = nullptr);

    void visit(const message_ns::TextMessage& message) override;

    void           connectToServer(const QHostAddress& address, quint16 port);
    void           disconnect();
    void           sendMessage(const message_ns::Message& message);
    const QString& name() const;
    void           setName(const QString& newName);

signals:
    void logMessage(const QString& message);
    void readyForPreparingToGameStart();
    void messageReceived(const std::unique_ptr<message_ns::Message>& message);
    void readyToStartGame();
    void selectMapRequest(QString mapFilename);
    void connectedToServer();

private slots:
    void onMessageReceived(const std::unique_ptr<message_ns::Message>& message);
    void onConnectedToServer();
    void onSocketError(QAbstractSocket::SocketError error);

private: // methods
    void sendPlayerNameMessage();

private: // data
    Socket*              socket_;
    QString              name_;
    object_id_t          playerId_;
    std::shared_ptr<Map> initializedMap_ = nullptr;
    // IMessageVisitor interface
public:
    void        visit(const message_ns::PrepareToStartGame& message) override;
    object_id_t playerId() const;

    // IMessageVisitor interface
public:
    void visit(const message_ns::SetPlayerIdMessage& message) override;
    void visit(const message_ns::SelectMapRequestMessage& message) override;

    // IMessageVisitor interface
public:
    const std::shared_ptr<Map>& initializedMap() const;
};

} // namespace bm

#endif // BM_CLIENT_HPP
