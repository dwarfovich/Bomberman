#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "character.hpp"
#include "direction.hpp"
#include "bomb.hpp"
#include "collider.hpp"

#include <memory>

namespace bm {

namespace bomberman_ns {
inline constexpr size_t defaultSpeed      = 10;
inline constexpr size_t defaultBombRadius = 1;
} // namespace bomberman_ns

class Bomberman : public Character
{
public:
    ACCEPT_COLLISION;

    Bomberman();

    CharacterType type() const override;
    void          toStream(QDataStream& stream) const override;
    void          fromStream(QDataStream& stream) override;
    bool          acceptsModifiers() const override;

    size_t                possibleSpeed() const;
    void                  setPossibleSpeed(size_t possibleSpeed);
    const Bomb&           bombPrototype() const;
    void                  setBombPrototype(const Bomb& Bomb);
    uint8_t               activeBombs() const;
    uint8_t               maxActiveBombs() const;
    void                  setMaxActiveBombs(uint8_t maxActiveBombs);
    void                  decreaseActiveBombs();
    std::unique_ptr<Bomb> createBomb();

private:
    uint8_t activeBombs_    = 0;
    uint8_t maxActiveBombs_ = 1;
    size_t  possibleSpeed_  = bomberman_ns::defaultSpeed;
    Bomb    bombPrototype_;
};
} // namespace bm

#endif // BOMBERMAN_HPP
