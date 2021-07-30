#include "moving_object.hpp"

namespace bm {

MovingObject::MovingObject(const MoveData& data) : data_ { data }
{}

const bm::MoveData& bm::MovingObject::movementData() const
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
{
}

} // namespace bm
