#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

#include "game_object.hpp"
#include "move_data.hpp"

namespace bm {

class MovingObject : public GameObject
{
public:
    MovingObject(const MoveData& data = {});

    virtual const MoveData& movementData() const;
    virtual void            setMovementData(const MoveData& data);
    virtual void            setSpeed(int speed);
    virtual int             speed() const;
    virtual void            setDirection(Direction direction);
    virtual const QPoint&   coordinates() const;
    virtual void            setCoordinates(const QPoint& coordinates);

private:
    MoveData data_;
};

} // namespace bm

#endif // MOVING_OBJECT_HPP
