#ifndef BM_CLIENT_HPP
#define BM_CLIENT_HPP

#include "message.hpp"
#include "i_message_visitor.hpp"

#include <QObject>
#include <QAbstractSocket>

QT_BEGIN_NAMESPACE
class QHostAddress;
QT_END_NAMESPACE

namespace bm {
class Socket;

class Client : public QObject, public IMessageVisitor
{
    Q_OBJECT
public:
    explicit Client(QObject* parent = nullptr);

    void visit(const TextMessage& message) override;

    void           connectToServer(const QHostAddress& address, quint16 port);
    void           disconnect();
    void           sendMessage(const Message& message);
    const QString& name() const;
    void           setName(const QString& newName);

signals:
    void logMessage(const QString& message);

private slots:
    void onMessageReceived(const std::unique_ptr<Message>& message);
    void onConnectedToServer();
    void onSocketError(QAbstractSocket::SocketError error);

private: // methods
    void sendPlayerNameMessage();

private: // data
    Socket* socket_;
    QString name_;
};

} // namespace bm

#endif // BM_CLIENT_HPP
