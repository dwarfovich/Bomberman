#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "direction.hpp"

#include <QPoint>
#include <QPointF>

namespace bm {
struct Character {
    size_t speed = 0;
    Direction direction = Direction::Downward;
    QPoint location = {0, 0};
    QPointF preciseLocation = {0., 0.};
};
}  // namespace bm

#endif  // CHARACTER_HPP
