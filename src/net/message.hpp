#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "message_type.hpp"

#include <Qt>

#define REGISTER_MESSAGE_MAKER(messageType, T) \
    namespace {                                \
    static MessageMaker<T> maker(messageType); \
    } // namespace

QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE

namespace bm {
class IMessageVisitor;

inline const qint64 messageHeaderSize = sizeof(MessageType) + sizeof(int);

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

} // namespace bm

#endif // MESSAGE_HPP
