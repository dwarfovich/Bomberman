#ifndef BM_BOMB_EXPLOSION_HPP
#define BM_BOMB_EXPLOSION_HPP

#include "explosion.hpp"

#include <vector>

namespace bm {
class GameObject;
struct Bomb;
class Map;

struct BombExplosionResult
{
    BombExplosionResult();

    Explosion                explosion;
    std::vector<GameObject*> affectedObjects;
};

BombExplosionResult explodeBomb(Map& map, Bomb& bomb);

} // namespace bm

#endif // BM_BOMB_EXPLOSION_HPP
