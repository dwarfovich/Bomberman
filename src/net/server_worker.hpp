#ifndef BM_SERVERWORKER_HPP
#define BM_SERVERWORKER_HPP

#include "messages/message.hpp"

#include <QObject>

class QTcpSocket;

namespace bm {
class Message;
class Socket;

class ServerWorker : public QObject
{
    Q_OBJECT

public:
    explicit ServerWorker(QObject* parent = nullptr);
    ServerWorker(const ServerWorker&) = delete;
    ServerWorker(ServerWorker&&)      = delete;
    ~ServerWorker();
    ServerWorker& operator=(const ServerWorker&) = delete;
    ServerWorker& operator=(ServerWorker&&) = delete;

    bool           isValid() const;
    bool           setSocketDescriptor(qintptr descriptor);
    const QString& clientName() const;
    void           setClientName(const QString& newClientName);
    void           sendMessage(const message_ns::Message& message);

    uint8_t clientId() const;

signals:
    void messageReceived(const std::unique_ptr<message_ns::Message>& message);
    void clientDisconnected();

private: // methods
    static uint8_t nextId();

private: // data
    Socket* socket_;
    QString clientName_ = "Unknown";
    uint8_t clientId_;

    static uint8_t              nextClientId_;
    static std::vector<uint8_t> freedIds;
    static constexpr uint8_t    invalidClientId = -1;
};

} // namespace bm

#endif // BM_SERVERWORKER_HPP
