#include "imodifier.hpp"

namespace bm {

ModifierDurationType IModifier::durationType() const
{
    return ModifierDurationType::Temporary;
}

Milliseconds IModifier::duration() const
{
    return Milliseconds { 3000 };
}

} // namespace bm
