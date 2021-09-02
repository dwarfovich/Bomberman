#ifndef BOMB_HPP
#define BOMB_HPP

#include "game_object.hpp"
#include "time.hpp"

#include <QDataStream>

#include <memory>

namespace bm {
class Bomberman;

class Bomb : public GameObject
{
public:
    friend QDataStream& operator<<(QDataStream& stream, const Bomb& bomb);
    friend QDataStream& operator>>(QDataStream& stream, Bomb& bomb);

    object_id_t  ownerId;
    int          radius    = 1;
    size_t       cellIndex = 0;
    Milliseconds explosionDelay { 1000 };
    Milliseconds explosionPeriod { 500 };
};

} // namespace bm

#endif // BOMB_HPP
