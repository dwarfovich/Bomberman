#include "moving_object.hpp"

#include <QDataStream>

namespace bm {

QDataStream& operator<<(QDataStream& stream, const MovingObject& object)
{
    stream << object.type();
    stream << object.data_;
    object.toStream(stream);

    return stream;
}

MovingObject::MovingObject(const MoveData& data) : data_ { data }
{}

void MovingObject::toStream(QDataStream& stream) const
{
    stream << data_;
}

const MoveData& MovingObject::movementData() const
{
    return data_;
}

void MovingObject::setMovementData(const MoveData& data)
{
    data_ = data;
}

void MovingObject::setSpeed(int speed)
{
    data_.speed = speed;
    if ((data_.direction == Direction::Upward || data_.direction == Direction::Left) && speed > 0) {
        data_.speed *= -1;
    } else if ((data_.direction == Direction::Downward || data_.direction == Direction::Right) && speed < 0) {
        data_.speed *= -1;
    }
}

int MovingObject::speed() const
{
    return data_.speed;
}

Direction MovingObject::direction() const
{
    return data_.direction;
}

void MovingObject::setDirection(Direction direction)
{
    data_.direction = direction;
    if ((direction == Direction::Left || direction == Direction::Upward) && data_.speed > 0) {
        data_.speed *= -1;
    } else if ((direction == Direction::Right || direction == Direction::Downward) && data_.speed < 0) {
        data_.speed *= -1;
    }
}

const QPoint& MovingObject::coordinates() const
{
    return data_.coordinates;
}

void MovingObject::setCoordinates(const QPoint& coordinates)
{
    data_.coordinates = coordinates;
}

bool MovingObject::notifyIfMeetedWall() const
{
    return false;
}

void MovingObject::meetsWall()
{}

} // namespace bm
