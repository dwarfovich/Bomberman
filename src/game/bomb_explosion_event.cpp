#include "bomb_explosion_event.hpp"

namespace bm {

BombExplosionEvent::BombExplosionEvent(const std::shared_ptr<Bomb> &aBomb, std::function<void(const BombPtr&)> aCallback)
    : bomb{aBomb}
    , callback{aCallback}
{}

void BombExplosionEvent::doWork() const
{
    callback(bomb);
}

} // namespace bm
