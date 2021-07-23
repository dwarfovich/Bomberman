#ifndef GAME_OBJECT_VARIANT_H
#define GAME_OBJECT_VARIANT_H

//#include "cell.hpp"
//#include "bomberman.hpp"
//#include "bot.hpp"

#include <memory>
#include <variant>

namespace bm {
class Cell;
class Bomberman;
class Bot;

using GameObjectVariant = std::variant<Cell*, std::shared_ptr<Bomberman>, std::shared_ptr<Bot>>;

} // namespace bm

#endif // GAME_OBJECT_VARIANT_H
