#include "modifier_factory.hpp"
#include "permanent_bomb_radius_increase.hpp"

namespace bm {

std::unique_ptr<IModifier> ModifierFactory::createModifier(ModifierType type)
{
    std::unique_ptr<IModifier> modifier = nullptr;
    switch (type) {
        case ModifierType::IncreaseBombRadius: modifier = std::make_unique<PermanentBombRadiusIncrease>(); break;
    }

    return modifier;
}

} // namespace bm
