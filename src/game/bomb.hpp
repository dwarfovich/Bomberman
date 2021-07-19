#ifndef BOMB_HPP
#define BOMB_HPP

#include "game_object.hpp"
#include "time.hpp"

#include <memory>

namespace bm {
class Bomberman;

struct Bomb : public GameObject
{
    std::shared_ptr<Bomberman> owner     = nullptr;
    int                        radius    = 1;
    size_t                     cellIndex = 0;
    Milliseconds               explosionDelay { 1000 };
};

} // namespace bm

#endif // BOMB_HPP
