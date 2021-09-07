#include "move_data.hpp"

#include <QDataStream>

namespace bm {

QDataStream& operator<<(QDataStream& stream, const MoveData& data)
{
    stream << data.speed;
    stream << data.possibleSpeed;
    stream << data.direction;
    stream << data.coordinates;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, MoveData& data)
{
    stream >> data.speed;
    stream >> data.possibleSpeed;
    stream >> data.direction;
    stream >> data.coordinates;

    return stream;
}

} // namespace bm
