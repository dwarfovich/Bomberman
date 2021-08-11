#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>

#include <vector>

namespace bm {
class ServerWorker;

inline const quint16 defaultPort = 44100;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);

    void setServerPort(quint16 port);

signals:
    void logMessageRequest(const QString& message);
    void clientConnected();

protected:
    void incomingConnection(qintptr descriptor) override;

private slots:
    void onUserDisconnected(bm::ServerWorker* client);

private:
    std::vector<ServerWorker*> clients_;
};

} // namespace bm

#endif // SERVER_HPP
