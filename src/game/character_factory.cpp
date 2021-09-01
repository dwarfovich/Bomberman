#include "character_factory.hpp"
#include "bomberman.hpp"
#include "bot.hpp"

namespace bm {

std::unique_ptr<Character> createCharacter(CharacterType type)
{
    if (type == CharacterType::Bomberman) {
        return std::make_unique<Bomberman>();
    } else if (type == CharacterType::Bot) {
        return std::make_unique<Bot>();
    } else {
        return nullptr;
    }
}

} // namespace bm
