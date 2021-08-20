#ifndef BM_MODIFIERFACTORY_HPP
#define BM_MODIFIERFACTORY_HPP

#include "modifier_type.hpp"

#include <memory>

namespace bm {
class IModifier;

class ModifierFactory
{
public:
    std::unique_ptr<IModifier> createModifier(ModifierType type);
};

} // namespace bm

#endif // BM_MODIFIERFACTORY_HPP
