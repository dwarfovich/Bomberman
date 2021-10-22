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

    friend QDataStream& operator<<(QDataStream& stream, const Explosion& explosion);
    friend QDataStream& operator>>(QDataStream& stream, Explosion& explosion);

    Explosion() = default;
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

    object_id_t bombOwner() const;
    void        setBombOwner(object_id_t newBombOwner);

private:
    CellLocation              center_;
    std::pair<size_t, size_t> xMinMax_;
    std::pair<size_t, size_t> yMinMax_;
    object_id_t               bombOwner_;
};

} // namespace bm

#endif // EXPLOSION_H
