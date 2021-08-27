#include "permanent_modifier.hpp"

namespace bm {

ModifierDurationType PermanentModifier::durationType() const
{
    return ModifierDurationType::Permanent;
}

Milliseconds PermanentModifier::duration() const
{
    return Milliseconds { 0 };
}

void PermanentModifier::deactivate(Bomberman &)
{}

} // namespace bm
