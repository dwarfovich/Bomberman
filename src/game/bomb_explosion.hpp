#ifndef BM_BOMB_EXPLOSION_HPP
#define BM_BOMB_EXPLOSION_HPP

#include "explosion.hpp"

#include <memory>
#include <vector>

namespace bm {
class GameObject;
class Bomb;
class Map;

struct BombExplosionResult
{
    BombExplosionResult();
    BombExplosionResult(const std::shared_ptr<Explosion>& aExplosion, const std::vector<GameObject*>& aAffectedObjects);

    std::shared_ptr<Explosion> explosion;
    std::vector<GameObject*>   affectedObjects;
};

BombExplosionResult explodeBomb(Map& map, Bomb& bomb);

} // namespace bm

#endif // BM_BOMB_EXPLOSION_HPP
