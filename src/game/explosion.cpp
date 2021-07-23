#include "explosion.hpp"
#include "map_constants.hpp"

namespace bm {

Explosion::Explosion(const std::pair<size_t, size_t> &xMinMax, const std::pair<size_t, size_t> &yMinMax)
{
    if (xMinMax.first != invalidMapIndex && xMinMax.second != invalidMapIndex && yMinMax.first != invalidMapIndex
        && yMinMax.second != invalidMapIndex) {
        xMinMax_ = xMinMax;
        yMinMax_ = yMinMax;
        for (size_t i = xMinMax_.first; i <= xMinMax_.second; ++i) {
            if (i % yMinMax_.first == 0) {
                center_ = i;
                break;
            }
        }
    }
}

const std::pair<size_t, size_t> &Explosion::xMinMax() const
{
    return xMinMax_;
}

const std::pair<size_t, size_t> &Explosion::yMinMax() const
{
    return yMinMax_;
}

size_t Explosion::center() const
{
    return center_;
}

} // namespace bm
