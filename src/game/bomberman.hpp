#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include "character.hpp"
#include "direction.hpp"

#include <memory>

namespace bm {
struct Bomb;

inline constexpr size_t defaultBombermanSpeed      = 20;
inline constexpr size_t defaultBombermanBombRadius = 1;

class Bomberman : public Character, public std::enable_shared_from_this<Bomberman>
{
public:
    Bomberman();

    size_t                activeBombs() const;
    size_t                maxActiveBombs() const;
    void                  decreaseActiveBombs();
    std::unique_ptr<Bomb> createBomb();

private:
    size_t activeBombs_    = 0;
    size_t maxActiveBombs_ = 1;
};
} // namespace bm

#endif // BOMBERMAN_HPP
