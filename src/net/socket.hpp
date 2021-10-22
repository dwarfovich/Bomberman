#ifndef BM_SOCKET_HPP
#define BM_SOCKET_HPP

#include "messages/message.hpp"

#include <QObject>
#include <QDataStream>
#include <QAbstractSocket>

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QHostAddress;
QT_END_NAMESPACE

namespace bm {
namespace message_ns {
class Message;

}

class Socket : public QObject
{
    Q_OBJECT

public:
    Socket(QObject* parent = nullptr);

    Socket(const Socket&) = delete;
    Socket(Socket&&)      = delete;
    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&&) = delete;

    bool    isConnected() const;
    bool    setSocketDescriptor(qintptr descriptor);
    void    connectToHost(const QHostAddress& address, quint16 port);
    void    disconnectFromHost();
    void    sendMessage(const Message& message);
    QString errorString();

signals:
    void connected();
    void disconnected();
    void socketError(QAbstractSocket::SocketError error);
    void messageReceived(const std::unique_ptr<Message>& message);

private slots:
    void onReadyRead();

private: // methods
    void readHeader(QDataStream& stream);
    void readData(QDataStream& stream);

private: // data
    enum class MessageReadingStage : uint8_t
    {
        Header,
        Data
    };

    QTcpSocket*              socket_;
    MessageReadingStage      currentStage_       = MessageReadingStage::Header;
    int                      currentMessageSize_ = 0;
    std::unique_ptr<Message> currentMessage_     = nullptr;
};

} // namespace bm

#endif // BM_SOCKET_HPP
