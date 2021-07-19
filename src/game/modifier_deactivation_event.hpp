#ifndef BM_MODIFIERDEACTIVATIONEVENT_HPP
#define BM_MODIFIERDEACTIVATIONEVENT_HPP

#include "timer_event.hpp"

#include <memory>

namespace bm {
class Bomberman;
class IModifier;

class ModifierDeactivationEvent : public TimerEvent
{
public:
    ModifierDeactivationEvent(const std::shared_ptr<Bomberman>& bomberman, const std::shared_ptr<IModifier>& modifier);

    void doWork() const override;

private:
    std::shared_ptr<Bomberman> bomberman_;
    std::shared_ptr<IModifier> modifier_;
};

} // namespace bm

#endif // BM_MODIFIERDEACTIVATIONEVENT_HPP
