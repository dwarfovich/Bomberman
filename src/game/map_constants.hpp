#ifndef MAP_CONSTANTS_HPP
#define MAP_CONSTANTS_HPP

#include "cell_location.hpp"

#include <QPoint>

namespace bm {

inline constexpr size_t       invalidMapIndex     = -1;
inline constexpr QPoint       invalidCoordinates  = { -1, -1 };
inline constexpr CellLocation invalidCellLocation = { invalidMapIndex, invalidMapIndex };
inline constexpr int          cellSize            = 100;
inline constexpr int          cellHalfSize        = cellSize / 2;

} // namespace bm

#endif // MAP_CONSTANTS_HPP
