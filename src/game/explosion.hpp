#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "game_object.hpp"
#include "cell_location.hpp"
#include "collider.hpp"

#include <utility>

namespace bm {

class Explosion : public GameObject
{
public:
    ACCEPT_COLLISION;

    Explosion(const CellLocation&              center,
              const std::pair<size_t, size_t>& xMinMax,
              const std::pair<size_t, size_t>& yMinMax);

    size_t                           xMin() const;
    size_t                           xMax() const;
    size_t                           yMin() const;
    size_t                           yMax() const;
    const std::pair<size_t, size_t>& xMinMax() const;
    const std::pair<size_t, size_t>& yMinMax() const;
    const CellLocation&              center() const;

private:
    CellLocation              center_;
    std::pair<size_t, size_t> xMinMax_;
    std::pair<size_t, size_t> yMinMax_;
};

} // namespace bm

#endif // EXPLOSION_H
