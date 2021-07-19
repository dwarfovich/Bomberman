#ifndef CELLLOCATION_HPP
#define CELLLOCATION_HPP

namespace bm {

class CellLocation
{
public:
    constexpr CellLocation();
    constexpr CellLocation(size_t aX, size_t aY) : x_ { aX }, y_ { aY } {}

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
