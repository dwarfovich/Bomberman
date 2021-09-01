#include "bomb_explosion_finished_event.hpp"

namespace bm {

BombExplosionFinishedEvent::BombExplosionFinishedEvent(const ExplosionPtr &                      explosion,
                                                       std::function<void(const ExplosionPtr &)> callback)
    : explosion_ { explosion }, callback_ { callback }
{}

void BombExplosionFinishedEvent::doWork() const
{
    callback_(explosion_);
}

} // namespace bm
