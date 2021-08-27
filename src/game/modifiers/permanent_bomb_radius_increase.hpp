#ifndef BM_PERMANENTBOMBRADIUSINCREASE_HPP
#define BM_PERMANENTBOMBRADIUSINCREASE_HPP

#include "permanent_modifier.hpp"

namespace bm {

class PermanentBombRadiusIncrease : public PermanentModifier
{
public:
    ModifierType type() const override;
    void         activate(Bomberman &bomberman) override;
};

} // namespace bm

#endif // BM_PERMANENTBOMBRADIUSINCREASE_HPP
