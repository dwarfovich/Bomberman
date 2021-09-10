#include "text_message.hpp"
#include "message_maker.hpp"
#include "i_message_visitor.hpp"

#include <QDataStream>

namespace bm {
namespace message_ns {

REGISTER_MESSAGE_MAKER(MessageType::Text, TextMessage);

TextMessage::TextMessage(const QString &text) : data_ { text.toUtf8() }
{}

MessageType TextMessage::type() const
{
    return MessageType::Text;
}

int TextMessage::dataLength() const
{
    return data_.size();
}

QString TextMessage::toString() const
{
    return QString::fromUtf8(data_);
}

void TextMessage::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

void TextMessage::fromStream(QDataStream &stream)
{
    stream >> data_;
}

void TextMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace message_ns
} // namespace bm
