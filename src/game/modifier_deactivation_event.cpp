#include "modifier_deactivation_event.hpp"
#include "modifiers/imodifier.hpp"

#include <QDebug>

namespace bm {

ModifierDeactivationEvent::ModifierDeactivationEvent(const std::shared_ptr<Bomberman>& bomberman,
                                                     const std::shared_ptr<IModifier>& modifier)
    : bomberman_ { bomberman }, modifier_ { modifier }
{}

void ModifierDeactivationEvent::doWork() const
{
    modifier_->deactivate(*bomberman_);
}

} // namespace bm
