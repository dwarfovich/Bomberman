#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "character.hpp"
#include "direction.hpp"

namespace bm {
inline constexpr size_t defaultBombermanSpeed = 5;
inline constexpr size_t defaultBombermanBombRadius = 1;

struct Bomberman : public Character {
    Bomberman();
    // player
};
}  // namespace bm

#endif // BOMBERMAN_HPP
