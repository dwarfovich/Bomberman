#ifndef MOVE_DATA_HPP
#define MOVE_DATA_HPP

#include "direction.hpp"

#include <QPoint>

namespace bm {

struct MoveData
{
    int       speed       = 0;
    Direction direction   = Direction::Downward;
    QPoint    coordinates = { 0, 0 };
};

} // namespace bm

#endif // MOVE_DATA_HPP
