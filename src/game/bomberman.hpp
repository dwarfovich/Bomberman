#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "character.hpp"
#include "direction.hpp"
#include "bomb.hpp"
#include "collider.hpp"

#include <memory>

namespace bm {

inline constexpr size_t defaultBombermanSpeed      = 10;
inline constexpr size_t defaultBombermanBombRadius = 1;

class Bomberman : public Character, public std::enable_shared_from_this<Bomberman>
{
public:
    ACCEPT_COLLISION;

    Bomberman();

    ObjectType type() const override;
    void       toStream(QDataStream& stream) const override;
    bool       acceptsModifiers() const override;

    size_t                activeBombs() const;
    size_t                maxActiveBombs() const;
    void                  decreaseActiveBombs();
    std::unique_ptr<Bomb> createBomb();

    const Bomb& bombPrototype() const;
    void        setBombPrototype(const Bomb& Bomb);

    size_t id() const;
    void   setId(size_t id);

private:
    size_t id_             = 0;
    size_t activeBombs_    = 0;
    size_t maxActiveBombs_ = 1;
    Bomb   bombPrototype_;
    ;
};
} // namespace bm

#endif // BOMBERMAN_HPP
