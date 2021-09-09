#include "explosion_finished_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::ExplosionFinished, ExplosionFinishedMessage);

ExplosionFinishedMessage::ExplosionFinishedMessage(object_id_t id) : explosionId_ { id }
{}

MessageType ExplosionFinishedMessage::type() const
{
    return MessageType::ExplosionFinished;
}

void ExplosionFinishedMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int ExplosionFinishedMessage::dataLength() const
{
    return 1;
}

void ExplosionFinishedMessage::dataToStream(QDataStream &stream) const
{
    stream << explosionId_;
}

void ExplosionFinishedMessage::fromStream(QDataStream &stream)
{
    stream >> explosionId_;
}

object_id_t ExplosionFinishedMessage::explosionId() const
{
    return explosionId_;
}

} // namespace bm
