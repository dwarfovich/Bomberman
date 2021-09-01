#include "bomb.hpp"

#include "bomberman.hpp"

namespace bm {

QDataStream& operator<<(QDataStream& stream, const Bomb& bomb)
{
    stream << bomb.radius;
    stream << bomb.cellIndex;
    stream << bomb.explosionDelay;
    stream << bomb.explosionPeriod;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Bomb& bomb)
{
    stream >> bomb.radius;
    stream >> bomb.cellIndex;
    stream >> bomb.explosionDelay;
    stream >> bomb.explosionPeriod;

    return stream;
}

} // namespace bm
