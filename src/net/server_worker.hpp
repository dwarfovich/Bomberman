#ifndef BM_SERVERWORKER_HPP
#define BM_SERVERWORKER_HPP

#include "message.hpp"

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

    bool           setSocketDescriptor(qintptr descriptor);
    const QString& clientName() const;
    void           setClientName(const QString& newClientName);
    void           sendMessage(const Message& message);

signals:
    void messageReceived(const std::unique_ptr<bm::Message>& message);
    void clientDisconnected();

private:
    Socket* socket_;
    QString clientName_ = "Unknown";
};

} // namespace bm

#endif // BM_SERVERWORKER_HPP
