#ifndef DIRECTION_HPP
#define DIRECTION_HPP

#include <QPoint>

namespace bm {

enum class Direction : size_t
{
    Left,
    Upward,
    Right,
    Downward
};

inline constexpr QPoint coordinatesShiftByDirection[] = { { -1, 0 }, { 0, -1 }, { 1, 0 }, { 0, 1 } };

inline constexpr size_t directionToIndex(Direction direction)
{
    return static_cast<size_t>(direction);
}

inline constexpr QPoint coordinatesShift(Direction direction)
{
    return coordinatesShiftByDirection[directionToIndex(direction)];
}

inline QPoint directionMultiplier(Direction direction)
{
    switch (direction) {
        case Direction::Upward: return { 1, -1 };
        case Direction::Right:
        case Direction::Downward: return { 1, 1 };
        case Direction::Left: return { -1, 1 };
    }
}

} // namespace bm

#endif // DIRECTION_HPP
