#include "server_game.hpp"
#include "bomb_explosion.hpp"
#include "bomb_explosion_event.hpp"
#include "bomb_explosion_finished_event.hpp"
#include "modifier_deactivation_event.hpp"

namespace bm {

void ServerGame::movePlayer(object_id_t player, Direction direction)
{
    auto bomberman = map_->character(player);
    if (bomberman) {
        bomberman->setSpeed(bomberman->possibleSpeed());
        bomberman->setDirection(direction);
        emit characterStartedMoving(bomberman);
    }
}

void ServerGame::stopPlayer(object_id_t player)
{
    auto bomberman = map_->character(player);
    if (bomberman) {
        bomberman->setSpeed(0);
        emit characterStopped(bomberman);
    }
}

std::shared_ptr<Bomb> ServerGame::placeBomb(object_id_t player)
{
    auto bomberman = map_->bomberman(player);
    if (bomberman && bomberman->canCreateBomb()) {
        std::shared_ptr<Bomb> bomb  = bomberman->createBomb();
        auto                  index = map_->coordinatesToIndex(bomberman->coordinates());
        if (map_->isProperIndex(index)) {
            bomb->cellIndex = index;
            map_->placeBomb(bomb);
            addExplosionEvent(bomb);
            emit bombPlaced(bomb);
        }
        return bomb;
    } else {
        static const std::shared_ptr<Bomb> empty;
        return empty;
    }
}

const std::shared_ptr<Bomberman>& ServerGame::bomberman(object_id_t playerId) const
{
    return map_->bomberman(playerId);
}

object_id_t ServerGame::playerId() const
{
    return 0;
}

} // namespace bm
