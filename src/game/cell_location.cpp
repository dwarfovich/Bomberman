#include "cell_location.hpp"
#include "map_constants.hpp"

namespace bm {

constexpr CellLocation::CellLocation() : x_ { invalidMapIndex }, y_ { invalidMapIndex }
{}

// constexpr CellLocation::CellLocation(size_t aX, size_t aY) : x_ { aX }, y_ { aY }
//{}

bool CellLocation::isValid() const
{
    return (x_ != invalidMapIndex && y_ != invalidMapIndex);
}

void CellLocation::setX(size_t newX)
{
    x_ = newX;
}

size_t CellLocation::y() const
{
    return y_;
}

void CellLocation::setY(size_t newY)
{
    y_ = newY;
}

void CellLocation::incrementX()
{
    if (isValid()) {
        ++x_;
    }
}

void CellLocation::decrementX()
{
    if (isValid()) {
        --x_;
    }
}

void CellLocation::incrementY()
{
    if (isValid()) {
        ++y_;
    }
}

void CellLocation::decrementY()
{
    if (isValid()) {
        --y_;
    }
}

size_t CellLocation::x() const
{
    return x_;
}

} // namespace bm
