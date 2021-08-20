#include "cell_location.hpp"
#include "map_constants.hpp"

#include <QDataStream>

namespace bm {

QDataStream& operator<<(QDataStream& stream, const CellLocation& location)
{
    stream << location.x_;
    stream << location.y_;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, CellLocation& location)
{
    stream >> location.x_;
    stream >> location.y_;

    return stream;
}

constexpr CellLocation::CellLocation() : x_ { invalidMapIndex }, y_ { invalidMapIndex }
{}

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
