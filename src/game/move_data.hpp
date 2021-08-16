#ifndef MOVE_DATA_HPP
#define MOVE_DATA_HPP

#include "direction.hpp"

#include <QPoint>

namespace bm {

struct MoveData
{
    friend QDataStream& operator<<(QDataStream& stream, const MoveData& data);

    int       speed       = 0;
    Direction direction   = Direction::Downward;
    QPoint    coordinates = { 0, 0 };
};

} // namespace bm

#endif // MOVE_DATA_HPP
