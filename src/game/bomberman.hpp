#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "character.hpp"
#include "direction.hpp"
#include "bomb.hpp"

#include <memory>

namespace bm {

inline constexpr size_t defaultBombermanSpeed      = 10;
inline constexpr size_t defaultBombermanBombRadius = 1;

class Bomberman : public Character, public std::enable_shared_from_this<Bomberman>
{
public:
    Bomberman();
    ALLOW_EXPLOSION_VISITOR;

    bool acceptsModifiers() const override;

    size_t                activeBombs() const;
    size_t                maxActiveBombs() const;
    void                  decreaseActiveBombs();
    std::unique_ptr<Bomb> createBomb();

    const Bomb& defaultBomb() const;
    void        setDefaultBomb(const Bomb& Bomb);

private:
    size_t activeBombs_    = 0;
    size_t maxActiveBombs_ = 1;
    Bomb   defaultBomb_;
};
} // namespace bm

#endif // BOMBERMAN_HPP
