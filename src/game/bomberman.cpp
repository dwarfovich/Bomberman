#include "bomberman.hpp"
#include "bomb.hpp"

namespace bm {

Bomberman::Bomberman() : Character { MoveData { 0, Direction::Downward, { 0, 0 } } }
{
    setBombPrototype({});
}

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
        auto bomb = std::make_unique<Bomb>(bombPrototype_);
        // bomb->owner = shared_from_this();
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
    bombPrototype_.playerId  = playerId_;
    bombPrototype_.cellIndex = 0;
}

uint8_t Bomberman::playerId() const
{
    return playerId_;
}

void Bomberman::setPlayerId(uint8_t newId)
{
    playerId_               = newId;
    bombPrototype_.playerId = playerId_;
}

ObjectType Bomberman::type() const
{
    return ObjectType::Bomberman;
}

void Bomberman::toStream(QDataStream &stream) const
{
    stream << playerId_;
    stream << activeBombs_;
    stream << maxActiveBombs_;
    stream << bombPrototype_;
}

void Bomberman::fromStream(QDataStream &stream)
{
    stream >> playerId_;
    stream >> activeBombs_;
    stream >> maxActiveBombs_;
    stream >> bombPrototype_;
}

} // namespace bm
