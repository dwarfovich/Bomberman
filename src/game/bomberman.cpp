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

uint8_t Bomberman::activeBombs() const
{
    return activeBombs_;
}

uint8_t Bomberman::maxActiveBombs() const
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
        return std::make_unique<Bomb>(bombPrototype_);
        ;
    } else {
        return nullptr;
    }
}

void Bomberman::setMaxActiveBombs(uint8_t maxActiveBombs)
{
    maxActiveBombs_ = maxActiveBombs;
}

size_t Bomberman::possibleSpeed() const
{
    return possibleSpeed_;
}

void Bomberman::setPossibleSpeed(size_t possibleSpeed)
{
    possibleSpeed_ = possibleSpeed;
}

const Bomb &Bomberman::bombPrototype() const
{
    return bombPrototype_;
    ;
}

void Bomberman::setBombPrototype(const Bomb &newBomb)
{
    bombPrototype_           = newBomb;
    bombPrototype_.ownerId_  = id();
    bombPrototype_.cellIndex = 0;
}

CharacterType Bomberman::type() const
{
    return CharacterType::Bomberman;
}

void Bomberman::toStream(QDataStream &stream) const
{
    stream << activeBombs_;
    stream << maxActiveBombs_;
    stream << bombPrototype_;
}

void Bomberman::fromStream(QDataStream &stream)
{
    stream >> activeBombs_;
    stream >> maxActiveBombs_;
    stream >> bombPrototype_;
}

} // namespace bm
