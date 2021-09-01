#ifndef BM_BOMBEXPLOSIONFINISHEDEVENT_HPP
#define BM_BOMBEXPLOSIONFINISHEDEVENT_HPP

#include "timer_event.hpp"

#include <memory>
#include <functional>

namespace bm {
class Explosion;

class BombExplosionFinishedEvent : public TimerEvent
{
public:
    using ExplosionPtr = std::shared_ptr<Explosion>;

    explicit BombExplosionFinishedEvent(const ExplosionPtr&                      explosion,
                                        std::function<void(const ExplosionPtr&)> callback);

    void doWork() const override;

private:
    std::shared_ptr<Explosion>               explosion_;
    std::function<void(const ExplosionPtr&)> callback_;
};

} // namespace bm

#endif // BM_BOMBEXPLOSIONFINISHEDEVENT_HPP
