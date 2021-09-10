#include "bomb_placed_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"
#include "game/bomb.hpp"

#include <QDataStream>

namespace bm {
namespace message_ns {

REGISTER_MESSAGE_MAKER(MessageType::BombPlaced, BombPlacedMessage);

BombPlacedMessage::BombPlacedMessage(const Bomb &bomb)
{
    QDataStream stream { &data_, QDataStream::WriteOnly };
    stream << bomb;
}

MessageType BombPlacedMessage::type() const
{
    return MessageType::BombPlaced;
}

void BombPlacedMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int BombPlacedMessage::dataLength() const
{
    return data_.size();
}

void BombPlacedMessage::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

void BombPlacedMessage::fromStream(QDataStream &stream)
{
    stream >> data_;
}

std::shared_ptr<Bomb> BombPlacedMessage::bomb() const
{
    auto        bomb = std::make_shared<Bomb>();
    QDataStream stream { data_ };
    stream >> *bomb;

    return bomb;
}

} // namespace message_ns
} // namespace bm
