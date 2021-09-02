#include "server_game.hpp"
#include "bomb_explosion.hpp"
#include "bomb_explosion_event.hpp"
#include "bomb_explosion_finished_event.hpp"
#include "modifier_deactivation_event.hpp"

namespace bm {

void ServerGame::start()
{
    //    moveTimer.start(updateTimeout_);
    Game::start();
}

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

void ServerGame::onCharacterIndexChanged(const std::shared_ptr<Character>& character, size_t index)
{
    const auto& cell      = map_->cell(index);
    const auto& modifier  = cell.modifier();
    const auto  bomberman = map_->bomberman(character->id());
    if (modifier && bomberman) {
        modifier->activate(*bomberman);
        if (modifier->durationType() == ModifierDurationType::Temporary) {
            auto event = std::make_unique<ModifierDeactivationEvent>(bomberman, cell.modifier());
            timerQueue.addEvent(createDelay(modifier->duration()), std::move(event));
        }
        map_->setModifier(cell.index(), nullptr);
    }
}

// void ServerGame::addPlayer(const std::shared_ptr<Bomberman>& player)
//{
//    player->setId(bombermans_.size());
//    bombermans_.push_back(player);
//    if (player->id() == 0) {
//        playerBomberman_ = player;
//    }
//}

void ServerGame::addExplosionEvent(const std::shared_ptr<Bomb>& bomb)
{
    auto callback = std::bind(&ServerGame::explodeBomb, this, std::placeholders::_1);
    timerQueue.addEvent(createDelay(bomb->explosionDelay), std::make_unique<BombExplosionEvent>(bomb, callback));
}

void ServerGame::explodeBomb(const std::shared_ptr<Bomb>& bomb)
{
    auto explosionData = bm::explodeBomb(*map_, *bomb);
    auto explosion     = explosionData.explosion;
    //    for (auto* affectedObject : explosionData.affectedObjects) {
    //        explosion->collideWith(*affectedObject, collider_);
    //    }
    auto callback = std::bind(&ServerGame::onExplosionFinished, this, std::placeholders::_1);
    timerQueue.addEvent(createDelay(bomb->explosionPeriod),
                        std::make_unique<BombExplosionFinishedEvent>(explosion, callback));

    auto bomberman = map_->bomberman(bomb->ownerId);
    if (bomberman) {
        bomberman->decreaseActiveBombs();
    }

    emit bombExploded(bomb);
    emit explosionHappened(explosion);
}

void ServerGame::setMap(const std::shared_ptr<Map>& map)
{
    if (map_.get()) {
        disconnect(map_.get(), &Map::characterIndexChanged, this, &ServerGame::onCharacterIndexChanged);
    }
    Game::setMap(map);
    connect(map_.get(), &Map::characterIndexChanged, this, &ServerGame::onCharacterIndexChanged);
}

object_id_t ServerGame::playerId() const
{
    return 0;
}

} // namespace bm
