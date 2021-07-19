#include "imodifier.hpp"

namespace bm {

ModifierType IModifier::type() const
{
    return ModifierType::Temporary;
}

Milliseconds IModifier::duration() const
{
    return Milliseconds { 3000 };
}

} // namespace bm
