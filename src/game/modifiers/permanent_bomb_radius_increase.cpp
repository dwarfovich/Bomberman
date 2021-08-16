#include "permanent_bomb_radius_increase.hpp"
#include "game/bomberman.hpp"
#include "game/bomb.hpp"

namespace bm {

ModifierType PermanentBombRadiusIncrease::type() const
{
    return ModifierType::IncreaseBombRadius;
}

void PermanentBombRadiusIncrease::activate(Bomberman &bomberman)
{
    auto bomb = bomberman.bombPrototype();
    ++bomb.radius;
    bomberman.setBombPrototype(bomb);
}

} // namespace bm
