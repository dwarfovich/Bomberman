#ifndef BM_PERMANENTMODIFIER_HPP
#define BM_PERMANENTMODIFIER_HPP

#include "imodifier.hpp"

namespace bm {

class PermanentModifier : public IModifier
{
public:
    ModifierDurationType durationType() const override;
    Milliseconds         duration() const override;
    void                 deactivate(Bomberman &) override;
};

} // namespace bm

#endif // BM_PERMANENTMODIFIER_HPP
