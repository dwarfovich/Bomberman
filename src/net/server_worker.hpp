#ifndef BM_SERVERWORKER_HPP
#define BM_SERVERWORKER_HPP

#include <QObject>

class QTcpSocket;

namespace bm {

class ServerWorker : public QObject
{
    Q_OBJECT

public:
    explicit ServerWorker(QObject* parent = nullptr);

    bool setSocketDescriptor(qintptr descriptor);

signals:
    void clientDisconnected();

private:
    QTcpSocket* socket_;
};

} // namespace bm

#endif // BM_SERVERWORKER_HPP
