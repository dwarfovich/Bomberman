#ifndef BM_SERVERWORKER_HPP
#define BM_SERVERWORKER_HPP

#include "message.hpp"

#include <QObject>

class QTcpSocket;

namespace bm {
class Message;

class ServerWorker : public QObject
{
    Q_OBJECT

public:
    explicit ServerWorker(QObject* parent = nullptr);
    ~ServerWorker();

    bool setSocketDescriptor(qintptr descriptor);

    const QString& clientName() const;
    void           setClientName(const QString& newClientName);
    void           sendMessage(const Message& message);

signals:
    void messageReceived(const std::unique_ptr<bm::Message>& message);
    void clientDisconnected();

private slots:
    void onReadyRead();

private:
    enum class MessageReadingStage : uint8_t
    {
        Header,
        Data
    };

    QTcpSocket*              socket_;
    MessageReadingStage      currentStage_       = MessageReadingStage::Header;
    int                      currentMessageSize_ = 0;
    std::unique_ptr<Message> currentMessage_     = nullptr;
    QString                  clientName_         = "Unknown";
};

} // namespace bm

#endif // BM_SERVERWORKER_HPP
