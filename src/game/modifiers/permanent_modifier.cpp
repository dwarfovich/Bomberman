#include "permanent_modifier.hpp"

namespace bm {

ModifierType PermanentModifier::type() const
{
    return ModifierType::Permanent;
}

Milliseconds PermanentModifier::duration() const
{
    return Milliseconds { 0 };
}

void PermanentModifier::deactivate(Bomberman &)
{}

} // namespace bm
