#include "set_player_id_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::SetPlayerId, SetPlayerIdMessage);

SetPlayerIdMessage::SetPlayerIdMessage(object_id_t playerId) : playerId_ { playerId }
{}

MessageType SetPlayerIdMessage::type() const
{
    return MessageType::SetPlayerId;
}

void SetPlayerIdMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int SetPlayerIdMessage::dataLength() const
{
    return sizeof(playerId_);
}

void SetPlayerIdMessage::dataToStream(QDataStream &stream) const
{
    stream << playerId_;
}

void SetPlayerIdMessage::fromStream(QDataStream &stream)
{
    stream >> playerId_;
}

object_id_t SetPlayerIdMessage::playerId() const
{
    return playerId_;
}

} // namespace bm