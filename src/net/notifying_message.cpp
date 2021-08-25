#include "notifying_message.hpp"
#include "i_message_visitor.hpp"

namespace bm {

int NotifyingMessage::dataLength() const
{
    return 0;
}

void NotifyingMessage::dataToStream(QDataStream &stream) const
{}

void NotifyingMessage::fromStream(QDataStream &stream)
{}

} // namespace bm
