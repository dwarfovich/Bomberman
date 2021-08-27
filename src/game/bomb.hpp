#ifndef BOMB_HPP
#define BOMB_HPP

#include "game_object.hpp"
#include "time.hpp"

#include <QDataStream>

#include <memory>

namespace bm {
class Bomberman;

struct Bomb : public GameObject
{
    friend QDataStream& operator<<(QDataStream& stream, const Bomb& bomb);
    friend QDataStream& operator>>(QDataStream& stream, Bomb& bomb);

    // std::shared_ptr<Bomberman> owner     = nullptr;
    uint8_t      playerId  = 0;
    int          radius    = 1;
    size_t       cellIndex = 0;
    Milliseconds explosionDelay { 1000 };
};

} // namespace bm

#endif // BOMB_HPP
