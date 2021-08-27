#include "character.hpp"

#include <QDataStream>

namespace bm {

Character::Character(const MoveData &moveData) : MovingObject { moveData }
{}

} // namespace bm
