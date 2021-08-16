#include "bomberman.hpp"
#include "bomb.hpp"

namespace bm {

Bomberman::Bomberman() : Character { MoveData { 0, Direction::Downward, { 0, 0 } } }
{}

bool Bomberman::acceptsModifiers() const
{
    return true;
}

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
        auto bomb   = std::make_unique<Bomb>(bombPrototype_);
        bomb->owner = shared_from_this();
        return bomb;
    } else {
        return nullptr;
    }
}

const Bomb &Bomberman::bombPrototype() const
{
    return bombPrototype_;
    ;
}

void Bomberman::setBombPrototype(const Bomb &newBomb)
{
    bombPrototype_           = newBomb;
    bombPrototype_.owner     = shared_from_this();
    bombPrototype_.cellIndex = 0;
}

size_t Bomberman::id() const
{
    return id_;
}

void Bomberman::setId(size_t newId)
{
    id_ = newId;
}

ObjectType Bomberman::type() const
{
    return ObjectType::Bomberman;
}

void Bomberman::toStream(QDataStream &stream) const
{
    stream << id_;
    stream << activeBombs_;
    stream << maxActiveBombs_;
    stream << bombPrototype_;
}

} // namespace bm
