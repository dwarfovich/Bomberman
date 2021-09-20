#include "player.hpp"

namespace bm {

QDataStream& operator<<(QDataStream& stream, const Player& player)
{
    stream << player.name_;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Player& player)
{
    stream >> player.name_;

    return stream;
}

Player::Player(const QString& filename) : filename_ { filename }
{}

const QString& Player::filename() const
{
    return filename_;
}

void Player::setFilename(const QString& newFilename)
{
    filename_ = newFilename;
}

const QString& Player::name() const
{
    return name_;
}

void Player::setName(const QString& newName)
{
    name_ = newName;
}

} // namespace bm
