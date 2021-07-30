#include "explosion.hpp"
#include "map_constants.hpp"

namespace bm {

Explosion::Explosion(const CellLocation &             center,
                     const std::pair<size_t, size_t> &xMinMax,
                     const std::pair<size_t, size_t> &yMinMax)
    : center_ { center }, xMinMax_ { xMinMax }, yMinMax_ { yMinMax }
{}

size_t Explosion::xMin() const
{
    return xMinMax_.first;
}

size_t Explosion::xMax() const
{
    return xMinMax_.second;
}

size_t Explosion::yMin() const
{
    return yMinMax_.first;
}

size_t Explosion::yMax() const
{
    return yMinMax_.second;
}

const std::pair<size_t, size_t> &Explosion::xMinMax() const
{
    return xMinMax_;
}

const std::pair<size_t, size_t> &Explosion::yMinMax() const
{
    return yMinMax_;
}

const CellLocation &Explosion::center() const
{
    return center_;
}

} // namespace bm
