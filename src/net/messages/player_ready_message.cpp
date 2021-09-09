#include "player_ready_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::MapInitialized, PlayerReadyMessage);

PlayerReadyMessage::PlayerReadyMessage(object_id_t playerId) : playerId_ { playerId }
{}

MessageType PlayerReadyMessage::type() const
{
    return MessageType::MapInitialized;
}

void PlayerReadyMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm

int bm::PlayerReadyMessage::dataLength() const
{
    return sizeof(playerId_);
}

void bm::PlayerReadyMessage::dataToStream(QDataStream &stream) const
{
    stream << playerId_;
}

void bm::PlayerReadyMessage::fromStream(QDataStream &stream)
{
    stream >> playerId_;
}
