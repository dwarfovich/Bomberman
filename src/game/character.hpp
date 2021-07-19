#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "moving_object.hpp"

namespace bm {
struct MoveData;

class Character : public MovingObject
{
public:
    Character(const MoveData& moveData = {});

    virtual bool acceptsModifiers() const = 0;
};

} // namespace bm

#endif // CHARACTER_HPP
