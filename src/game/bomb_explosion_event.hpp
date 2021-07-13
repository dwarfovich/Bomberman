#ifndef BM_BOMBEXPLOSIONEVENT_HPP
#define BM_BOMBEXPLOSIONEVENT_HPP

#include "timer_event.hpp"

#include <memory>
#include <functional>

namespace bm {
struct Bomb;

class BombExplosionEvent : public TimerEvent
{
public:
    using BombPtr = std::shared_ptr<Bomb>;
    explicit BombExplosionEvent(const BombPtr& aBomb, std::function<void(const BombPtr&)> aCallback);

    void doWork() const override;

private:
    std::shared_ptr<Bomb> bomb;
    std::function<void(const BombPtr&)> callback;
};

} // namespace bm

#endif // BM_BOMBEXPLOSIONEVENT_HPP
