#ifndef MESSAGE_H
#define MESSAGE_H

#include "message_type.hpp"

#include <Qt>

QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE

namespace bm {
class IMessageVisitor;

namespace message_ns {
inline const qint64 messageHeaderSize = sizeof(MessageType) + sizeof(int /*length*/);

class Message
{
public:
    friend QDataStream& operator<<(QDataStream& stream, const Message& message);
    friend QDataStream& operator>>(QDataStream& stream, Message& message);

    virtual ~Message() = default;

    virtual MessageType type() const                            = 0;
    virtual void        accept(IMessageVisitor& visitor)        = 0;
    virtual int         dataLength() const                      = 0;
    virtual void        dataToStream(QDataStream& stream) const = 0;
    virtual void        fromStream(QDataStream& stream)         = 0;
    virtual void        toStream(QDataStream& stream) const;
    virtual void        defaultHeaderToStream(QDataStream& stream) const;
};

} // namespace message_ns

} // namespace bm

#endif // MESSAGE_H
