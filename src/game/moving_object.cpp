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

void MovingObject::setDirection(Direction direction)
{
    data_.direction = direction;
}

void MovingObject::setCoordinates(const QPoint& coordinates)
{
    data_.coordinates = coordinates;
}

} // namespace bm
