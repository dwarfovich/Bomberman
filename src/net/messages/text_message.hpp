#ifndef BM_TEXTMESSAGE_HPP
#define BM_TEXTMESSAGE_HPP

#include "byte_array_message.hpp"
#include "message_type.hpp"

#include <QString>
#include <QByteArray>

namespace bm {

class TextMessage : public ByteArrayMessage<QString>
{
public:
    TextMessage(const QString& text = {});

    MessageType type() const override;
    void        accept(IMessageVisitor& visitor) override;
};

} // namespace bm

#endif // BM_TEXTMESSAGE_HPP
