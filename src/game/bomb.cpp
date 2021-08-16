#include "bomb.hpp"

#include "bomberman.hpp"

namespace bm {

QDataStream& operator<<(QDataStream& stream, const Bomb& bomb)
{
    stream << bomb.owner->id();
    stream << bomb.radius;
    stream << bomb.cellIndex;
    stream << bomb.explosionDelay;

    return stream;
}

} // namespace bm
