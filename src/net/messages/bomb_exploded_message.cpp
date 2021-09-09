#include "bomb_exploded_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"
#include "game/bomb.hpp"
#include "game/explosion.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::BombExploded, BombExplodedMessage);

BombExplodedMessage::BombExplodedMessage(const Bomb &bomb, const Explosion &explosion)
{
    QDataStream stream { &data_, QDataStream::WriteOnly };
    stream << bomb << explosion;
}

MessageType BombExplodedMessage::type() const
{
    return MessageType::BombExploded;
}

void BombExplodedMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int BombExplodedMessage::dataLength() const
{
    return data_.size();
}

void BombExplodedMessage::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

void BombExplodedMessage::fromStream(QDataStream &stream)
{
    stream >> data_;
}

std::pair<std::shared_ptr<Bomb>, std::shared_ptr<Explosion>> BombExplodedMessage::result() const
{
    std::pair<std::shared_ptr<Bomb>, std::shared_ptr<Explosion>> result { std::make_shared<Bomb>(),
                                                                          std::make_shared<Explosion>() };

    QDataStream stream { data_ };
    stream >> *result.first >> *result.second;

    return result;

    return {};
}

} // namespace bm
