#include "set_player_id_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::SetPlayerId, SetPlayerIdMessage);

SetPlayerIdMessage::SetPlayerIdMessage(object_id_t playerId) : ByteArrayMessage<object_id_t> { playerId }
{}

MessageType SetPlayerIdMessage::type() const
{
    return MessageType::SetPlayerId;
}

void SetPlayerIdMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
