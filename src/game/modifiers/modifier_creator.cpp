#include "modifier_creator.hpp"
#include "permanent_bomb_radius_increase.hpp"

namespace bm {

ModifierCreator::ModifierCreator() : randomEngine_ { randomDevice_() }
{
    modifiers_.push_back(std::make_shared<PermanentBombRadiusIncrease>());
    std::uniform_int_distribution<int> uniform_dist(0, modifiers_.size());
}

std::unique_ptr<IModifier> ModifierCreator::chooseModifier() const
{
    return std::make_unique<PermanentBombRadiusIncrease>();
}

} // namespace bm
