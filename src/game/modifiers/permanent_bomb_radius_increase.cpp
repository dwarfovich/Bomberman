#include "permanent_bomb_radius_increase.hpp"
#include "game/bomberman.hpp"
#include "game/bomb.hpp"

namespace bm {

void PermanentBombRadiusIncrease::activate(Bomberman &bomberman)
{
    auto bomb = bomberman.defaultBomb();
    ++bomb.radius;
    bomberman.setDefaultBomb(bomb);
}

} // namespace bm
