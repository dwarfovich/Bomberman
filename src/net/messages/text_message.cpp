#include "text_message.hpp"
#include "message_maker.hpp"
#include "i_message_visitor.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::Text, TextMessage);

TextMessage::TextMessage(const QString &text) : ByteArrayMessage<QString> { text }
{}

MessageType TextMessage::type() const
{
    return MessageType::Text;
}

void TextMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
