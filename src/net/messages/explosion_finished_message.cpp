#include "explosion_finished_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::ExplosionFinished, ExplosionFinishedMessage);

ExplosionFinishedMessage::ExplosionFinishedMessage(object_id_t id) : ByteArrayMessage<object_id_t> { id }
{}

MessageType ExplosionFinishedMessage::type() const
{
    return MessageType::ExplosionFinished;
}

void ExplosionFinishedMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
