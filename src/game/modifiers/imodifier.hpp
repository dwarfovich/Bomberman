#ifndef IMODIFIER_HPP
#define IMODIFIER_HPP

#include "time.hpp"

namespace bm {
class Bomberman;

enum class ModifierType : uint8_t
{
    Permanent,
    Temporary
};

class IModifier
{
public:
    virtual ModifierType type() const;
    virtual Milliseconds duration() const;

    virtual void activate(Bomberman& bomberman)   = 0;
    virtual void deactivate(Bomberman& bomberman) = 0;
};
} // namespace bm

#endif // IMODIFIER_HPP
