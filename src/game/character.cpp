#include "character.hpp"

#include <QDataStream>

namespace bm {

QDataStream& operator<<(QDataStream& stream, const Character& object)
{
    stream << object.type();
    stream << object.id_;
    stream << object.moveData_;
    object.toStream(stream);

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Character& object)
{
    stream >> object.id_;
    stream >> object.moveData_;
    object.fromStream(stream);

    return stream;
}

Character::Character(const MoveData& moveData) : moveData_ { moveData }
{}

void Character::toStream(QDataStream& stream) const
{
    stream << moveData_;
}

void Character::fromStream(QDataStream& stream)
{
    stream >> moveData_;
}

const MoveData& Character::movementData() const
{
    return moveData_;
}

void Character::setMovementData(const MoveData& data)
{
    moveData_ = data;
}

void Character::setSpeed(int speed)
{
    moveData_.speed = speed;
    if ((moveData_.direction == Direction::Upward || moveData_.direction == Direction::Left) && speed > 0) {
        moveData_.speed *= -1;
    } else if ((moveData_.direction == Direction::Downward || moveData_.direction == Direction::Right) && speed < 0) {
        moveData_.speed *= -1;
    }
}

int Character::speed() const
{
    return moveData_.speed;
}

Direction Character::direction() const
{
    return moveData_.direction;
}

void Character::setDirection(Direction direction)
{
    moveData_.direction = direction;
    if ((direction == Direction::Left || direction == Direction::Upward) && moveData_.speed > 0) {
        moveData_.speed *= -1;
    } else if ((direction == Direction::Right || direction == Direction::Downward) && moveData_.speed < 0) {
        moveData_.speed *= -1;
    }
}

const QPoint& Character::coordinates() const
{
    return moveData_.coordinates;
}

void Character::setCoordinates(const QPoint& coordinates)
{
    moveData_.coordinates = coordinates;
}

bool Character::notifyIfMeetedWall() const
{
    return false;
}

void Character::meetsWall()
{}

} // namespace bm
