#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "game_object.hpp"
#include "character_type.hpp"
#include "move_data.hpp"

namespace bm {

class Character : public GameObject
{
public:
    friend QDataStream& operator<<(QDataStream& stream, const Character& object);
    friend QDataStream& operator>>(QDataStream& stream, Character& object);

    Character(const MoveData& moveData = {});

    virtual CharacterType type() const                        = 0;
    virtual void          toStream(QDataStream& stream) const = 0;
    virtual void          fromStream(QDataStream& stream)     = 0;

    virtual const MoveData& movementData() const;
    virtual void            setMovementData(const MoveData& data);
    // TODO: make speed and possibleSpeed types be the same.
    virtual void setSpeed(int speed);
    virtual int  speed() const;
    virtual void setPossibleSpeed(int speed);
    virtual int  possibleSpeed() const;

    virtual Direction     direction() const;
    virtual void          setDirection(Direction direction);
    virtual const QPoint& coordinates() const;
    virtual void          setCoordinates(const QPoint& coordinates);
    virtual bool          notifyIfMeetedWall() const;
    virtual void          meetsWall();
    virtual bool          acceptsModifiers() const = 0;

private:
    MoveData moveData_;
};

} // namespace bm

#endif // CHARACTER_HPP
