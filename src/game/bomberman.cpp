#include "bomberman.hpp"
#include "bomb.hpp"

namespace bm {

Bomberman::Bomberman() : Character { MoveData { 0, Direction::Downward, { 0, 0 } } }
{}

size_t Bomberman::activeBombs() const
{
    return activeBombs_;
}

size_t Bomberman::maxActiveBombs() const
{
    return maxActiveBombs_;
}

void Bomberman::decreaseActiveBombs()
{
    if (activeBombs_ > 0) {
        --activeBombs_;
    }
}

std::unique_ptr<Bomb> Bomberman::createBomb()
{
    if (activeBombs_ < maxActiveBombs_) {
        ++activeBombs_;
        auto bomb    = std::make_unique<Bomb>();
        bomb->owner  = shared_from_this();
        bomb->radius = 1;
        return bomb;
    } else {
        return nullptr;
    }
}

} // namespace bm
