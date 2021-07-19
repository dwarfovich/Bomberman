#ifndef BM_MODIFIERCREATOR_HPP
#define BM_MODIFIERCREATOR_HPP

#include <memory>
#include <vector>
#include <random>

namespace bm {
class IModifier;

class ModifierCreator
{
public:
    ModifierCreator();

    const std::shared_ptr<IModifier>& chooseModifier() const;

private:
    std::vector<std::shared_ptr<IModifier>> modifiers_;
    std::random_device                      randomDevice_;
    std::default_random_engine              randomEngine_;
    std::uniform_int_distribution<size_t>   uniformDistribution_;
};

} // namespace bm

#endif // BM_MODIFIERCREATOR_HPP
