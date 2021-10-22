#include "message.hpp"

#include <QDataStream>

namespace bm {

QDataStream& operator<<(QDataStream& stream, const Message& message)
{
    message.toStream(stream);

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Message& message)
{
    message.fromStream(stream);

    return stream;
}

void Message::toStream(QDataStream& stream) const
{
    defaultHeaderToStream(stream);
    dataToStream(stream);
}

void Message::defaultHeaderToStream(QDataStream& stream) const
{
    stream << static_cast<uint8_t>(type());
    stream << dataLength();
}

} // namespace bm
