#ifndef MOVING_OBJECT_HPP
#define MOVING_OBJECT_HPP

#include "game_object.hpp"
#include "object_type.hpp"
#include "move_data.hpp"

namespace bm {

class MovingObject : public GameObject
{
public:
    friend QDataStream& operator<<(QDataStream& stream, const MovingObject& object);
    friend QDataStream& operator>>(QDataStream& stream, MovingObject& object);

    MovingObject(const MoveData& data = {});

    virtual ObjectType      type() const                        = 0;
    virtual void            toStream(QDataStream& stream) const = 0;
    virtual void            fromStream(QDataStream& stream)     = 0;
    virtual const MoveData& movementData() const;
    virtual void            setMovementData(const MoveData& data);
    virtual void            setSpeed(int speed);
    virtual int             speed() const;
    virtual Direction       direction() const;
    virtual void            setDirection(Direction direction);
    virtual const QPoint&   coordinates() const;
    virtual void            setCoordinates(const QPoint& coordinates);
    virtual bool            notifyIfMeetedWall() const;
    virtual void            meetsWall();

    uint8_t id() const;
    void    setId(uint8_t newId);

private:
    MoveData data_;
    uint8_t  id_;
};

} // namespace bm

#endif // MOVING_OBJECT_HPP
