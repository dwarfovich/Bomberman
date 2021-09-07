#ifndef BM_CHARACTERFACTORY_HPP
#define BM_CHARACTERFACTORY_HPP

#include "character_type.hpp"
#include "character.hpp"

#include <memory>

namespace bm {

std::unique_ptr<Character> createCharacter(CharacterType type);

} // namespace bm

#endif // BM_CHARACTERFACTORY_HPP
