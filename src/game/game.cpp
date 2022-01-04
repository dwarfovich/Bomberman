#include "game.hpp"
#include "time.hpp"
#include "bomb_explosion_event.hpp"
#include "bomb_explosion_finished_event.hpp"
#include "modifier_deactivation_event.hpp"
#include "map_constants.hpp"
#include "bomb_explosion.hpp"

#include "gui/game_scene.hpp"

#include <functional>

namespace bm {

Game::Game() : collider_ { this }
{
    connect(&movementTimer_, &QTimer::timeout, [this]() {
        map_->moveObjects(game_ns::movementUpdatePeriod);
    });
}

object_id_t Game::playerId() const
{
    return playerId_;
}

const std::shared_ptr<Bomberman>& Game::bomberman(object_id_t playerId) const
{
    return map_->bomberman(playerId);
}

void Game::start()
{
    setGameStatus(GameStatus::Playing);
    movementTimer_.start(game_ns::movementUpdatePeriod);
}

void Game::prepareToStart()
{}

void Game::setMap(const std::shared_ptr<Map>& map)
{
    // TODO: count connected and disconnected signals.
    if (map_) {
        disconnect(map_.get(), &Map::cellStructureChanged, this, &Game::cellStructureChanged);
        disconnect(map_.get(), &Map::characterMoved, this, &Game::characterMoved);
        disconnect(map_.get(), &Map::objectsCollided, this, &Game::onObjectsCollided);
        disconnect(map_.get(), &Map::characterIndexChanged, this, &Game::onCharacterIndexChanged);
        disconnect(map_.get(), &Map::modifierAdded, this, &Game::modifierAdded);
        disconnect(map_.get(), &Map::exitActivated, this, &Game::exitActivated);
        disconnect(map_.get(), &Map::characterDestroyed, this, &Game::characterDestroyed);
        disconnect(map_.get(), &Map::characterDestroyed, this, &Game::objectDestroyed);
    }
    map_ = map;
    connect(map_.get(), &Map::cellStructureChanged, this, &Game::cellStructureChanged);
    connect(map_.get(), &Map::characterMoved, this, &Game::characterMoved);
    connect(map_.get(), &Map::objectsCollided, this, &Game::onObjectsCollided);
    connect(map_.get(), &Map::characterIndexChanged, this, &Game::onCharacterIndexChanged);
    connect(map_.get(), &Map::modifierAdded, this, &Game::modifierAdded);
    connect(map_.get(), &Map::modifierRemoved, this, &Game::modifierRemoved);
    connect(map_.get(), &Map::exitActivated, this, &Game::exitActivated);
    connect(map_.get(), &Map::characterDestroyed, this, &Game::characterDestroyed);
    connect(map_.get(), &Map::characterDestroyed, this, &Game::objectDestroyed);
}

const std::shared_ptr<Map>& Game::map() const
{
    return map_;
}

void Game::setGameProcessHandler(std::unique_ptr<GameProcessHandler> handler)
{
    gameProcessHandler_ = std::move(handler);
}

void Game::onExplosionFinished(const std::shared_ptr<Explosion>& explosion)
{
    map_->removeExplosion(explosion->id());
    emit explosionFinished(explosion);
}

void Game::setGameStatus(GameStatus status)
{
    currentStatus_ = status;
    if (status == GameStatus::GameOver) {
        movementTimer_.stop();
    }
    emit gameStatusChanged(currentStatus_);
}

const GameResult& Game::gameResult() const
{
    return gameResult_;
}

void Game::addPlayer(const std::shared_ptr<Player>& player)
{
    players_.push_back(player);
}

GameStatus Game::currentStatus() const
{
    return currentStatus_;
}

object_id_t Game::getPlayerBomberman() const
{
    return playerId_;
}

void Game::setPlayerBomberman(object_id_t playerBomberman)
{
    playerId_ = playerBomberman;
}

void Game::onObjectsCollided(const Map::Collisions& collisions)
{
    for (const auto& [lhs, rhs] : collisions) {
        lhs->collideWith(*rhs, collider_);
    }
}

void Game::onCharacterIndexChanged(const std::shared_ptr<Character>& character, size_t index)
{
    const auto& cell      = map_->cell(index);
    const auto& modifier  = cell.modifier();
    const auto& bomberman = map_->bomberman(character->id());
    if (modifier && bomberman) {
        modifier->activate(*bomberman);
        if (modifier->durationType() == ModifierDurationType::Temporary) {
            auto event = std::make_unique<ModifierDeactivationEvent>(bomberman, cell.modifier());
            timerEventsQueue.addEvent(createDelay(modifier->duration()), std::move(event));
        }
        map_->setModifier(cell.index(), nullptr);
    }
}

void Game::addExplosionEvent(const std::shared_ptr<Bomb>& bomb)
{
    auto callback = std::bind(&Game::explodeBomb, this, std::placeholders::_1);
    timerEventsQueue.addEvent(createDelay(bomb->explosionDelay), std::make_unique<BombExplosionEvent>(bomb, callback));
}

void Game::explodeBomb(const std::shared_ptr<Bomb>& bomb)
{
    auto explosionData = bm::explodeBomb(*map_, *bomb);
    auto explosion     = explosionData.explosion;
    auto callback      = std::bind(&Game::onExplosionFinished, this, std::placeholders::_1);
    timerEventsQueue.addEvent(createDelay(bomb->explosionPeriod),
                              std::make_unique<BombExplosionFinishedEvent>(explosion, callback));

    auto bomberman = map_->bomberman(bomb->ownerId);
    if (bomberman) {
        bomberman->decreaseActiveBombs();
    }

    // TODO: Remove one of this signals.
    emit bombExploded(bomb);
    emit explosionHappened(explosion);
}

} // namespace bm
