#include "server_worker.hpp"

#include <QTcpSocket>

namespace bm {

ServerWorker::ServerWorker(QObject *parent) : QObject { parent }, socket_ { new QTcpSocket { this } }
{}

bool ServerWorker::setSocketDescriptor(qintptr descriptor)
{
    return socket_->setSocketDescriptor(descriptor);
}

} // namespace bm
