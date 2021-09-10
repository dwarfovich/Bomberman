#ifndef BM_TEXTMESSAGE_HPP
#define BM_TEXTMESSAGE_HPP

#include "message.hpp"
#include "message_type.hpp"

#include <QString>
#include <QByteArray>

namespace bm {
namespace message_ns {

class TextMessage : public Message
{
public:
    TextMessage(const QString& text = {});

    MessageType type() const override;
    void        accept(IMessageVisitor& visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream& stream) const override;
    void        fromStream(QDataStream& stream) override;

    QString toString() const;

private:
    QByteArray data_;
};

} // namespace message_ns
} // namespace bm

#endif // BM_TEXTMESSAGE_HPP
