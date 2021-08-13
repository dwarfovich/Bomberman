#ifndef BM_CLIENT_HPP
#define BM_CLIENT_HPP

#include "message.hpp"
#include "i_message_visitor.hpp"

#include <QObject>
#include <QAbstractSocket>

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QHostAddress;
QT_END_NAMESPACE

namespace bm {

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
    void onConnectedToServer();
    void onSocketError(QAbstractSocket::SocketError error);
    void onReadyRead();

private: // methods
    void sendPlayerNameMessage();

private:
    enum class MessageReadingStage : uint8_t
    {
        Header,
        Data
    };

    QTcpSocket*              socket_;
    QString                  name_;
    MessageReadingStage      currentStage_       = MessageReadingStage::Header;
    int                      currentMessageSize_ = 0;
    std::unique_ptr<Message> currentMessage_     = nullptr;
};

} // namespace bm

#endif // BM_CLIENT_HPP
