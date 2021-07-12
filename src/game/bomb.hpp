#ifndef BOMB_HPP
#define BOMB_HPP

#include <memory>

namespace bm {
class Bomberman;

struct Bomb
{
    std::shared_ptr<Bomberman> owner     = nullptr;
    int                        radius    = 0;
    size_t                     cellIndex = 0;
};

} // namespace bm

#endif // BOMB_HPP
