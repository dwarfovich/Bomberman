#include "character_moved_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"
#include "game/moving_object.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::CharacterMoved, CharacterMovedMessage);

CharacterMovedMessage::CharacterMovedMessage(const MovingObject &object)
{
    QDataStream stream { &data_, QDataStream::WriteOnly };
    stream << object.id();
    stream << object.movementData();
}

MessageType CharacterMovedMessage::type() const
{
    return MessageType::CharacterMoved;
}

void CharacterMovedMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int CharacterMovedMessage::dataLength() const
{
    return data_.size();
}

void CharacterMovedMessage::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

void CharacterMovedMessage::fromStream(QDataStream &stream)
{
    stream >> data_;
}

std::pair<uint8_t, MoveData> CharacterMovedMessage::moveData() const
{
    std::pair<uint8_t, MoveData> moveData;
    QDataStream                  stream { data_ };
    stream >> moveData.first >> moveData.second;

    return moveData;
}

} // namespace bm
