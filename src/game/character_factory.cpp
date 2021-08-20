#include "character_factory.hpp"
#include "bomberman.hpp"
#include "bot.hpp"

namespace bm {

std::unique_ptr<Character> createCharacter(ObjectType type)
{
    if (type == ObjectType::Bomberman) {
        return std::make_unique<Bomberman>();
    } else if (type == ObjectType::Bot) {
        return std::make_unique<Bot>();
    } else {
        return nullptr;
    }
}

} // namespace bm
