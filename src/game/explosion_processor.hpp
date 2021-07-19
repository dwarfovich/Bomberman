#ifndef EXPLOSIONPROCESSOR_HPP
#define EXPLOSIONPROCESSOR_HPP

#include "modifiers/modifier_creator.hpp"

#include <memory>

namespace bm {
struct Bomb;
struct Cell;
class Bomberman;
class GameObject;
class Game;

class ExplosionProcessor
{
public:
    explicit ExplosionProcessor(Game& game);
    void setBomb(const std::shared_ptr<Bomb>& bomb);

    void explode(GameObject& object);
    void explode(Cell& cell);
    void explode(Bomberman& bomberman);

private:
    Game&                 game_;
    ModifierCreator       modifierCreator_;
    std::shared_ptr<Bomb> bomb_ = nullptr;
};

} // namespace bm

#endif // EXPLOSIONPROCESSOR_HPP
