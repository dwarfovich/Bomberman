#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "game_object.hpp"

namespace bm {

class Explosion : public GameObject
{
public:
    Explosion(const std::pair<size_t, size_t> &xMinMax, const std::pair<size_t, size_t> &yMinMax);

    const std::pair<size_t, size_t> &xMinMax() const;
    const std::pair<size_t, size_t> &yMinMax() const;
    size_t                           center() const;

private:
    std::pair<size_t, size_t> xMinMax_;
    std::pair<size_t, size_t> yMinMax_;
    size_t                    center_;
};

} // namespace bm

#endif // EXPLOSION_H
