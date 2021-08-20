#ifndef CELLLOCATION_HPP
#define CELLLOCATION_HPP

#include <Qt>

QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE

namespace bm {

class CellLocation
{
public:
    constexpr CellLocation();
    constexpr CellLocation(size_t aX, size_t aY) : x_ { aX }, y_ { aY } {}

    friend QDataStream& operator<<(QDataStream& stream, const CellLocation& location);
    friend QDataStream& operator>>(QDataStream& stream, CellLocation& location);

    bool   isValid() const;
    size_t x() const;
    void   setX(size_t newX);
    size_t y() const;
    void   setY(size_t newY);
    void   incrementX();
    void   decrementX();
    void   incrementY();
    void   decrementY();

private:
    size_t x_;
    size_t y_;
};

} // namespace bm

#endif // CELLLOCATION_HPP
