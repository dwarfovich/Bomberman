#include "game.hpp"
#include "time.hpp"
#include "bomb_explosion_event.hpp"
#include "bomb_explosion_finished_event.hpp"
#include "modifier_deactivation_event.hpp"

#include "map_constants.hpp"
#include "bomb_explosion.hpp"

#include "gui/game_scene.hpp"
#include "gui/character_graphics_item.hpp"

#include <functional>

namespace bm {
Game::Game(QObject* parent) : QObject { parent }, collider_ { this }
{}

void Game::start()
{
    //    if (!scene_) {
    //        return;
    //    }
    // moveTimer.start(timeout_);
}

void Game::setMap(const std::shared_ptr<Map>& map)
{
    // TODO: Disconnect oldies.
    map_ = map;
    connect(map_.get(), &Map::cellChanged, this, &Game::cellChanged);
    connect(map_.get(), &Map::objectMoved, this, &Game::objectMoved);
    //    connect(map_.get(), &Map::objectIndexChanged, this, &Game::onObjectIndexChanged);
    //    connect(&moveTimer, &QTimer::timeout, [this]() {
    //        map_->moveObjects(timeout_);
    //    });
}
void Game::setPlayer1Bomberman(const std::shared_ptr<Bomberman>& player)
{
    player1_ = player;
}

bool Game::movePlayer1(Direction direction)
{
    player1_->setSpeed(defaultBombermanSpeed);
    player1_->setDirection(direction);

    return true;
}

void Game::stopPlayer1(Direction direction)
{
    if (player1_->movementData().direction == direction) {
        player1_->setSpeed(0);
    }
}

void Game::placeBomb1()
{
    std::shared_ptr<Bomb> bomb = player1_->createBomb();
    if (bomb) {
        auto index = map_->coordinatesToIndex(player1_->movementData().coordinates);
        if (map_->isProperIndex(index)) {
            bomb->cellIndex = index;
            map_->placeBomb(bomb);
            addExplosionEvent(bomb);
        }
    }
}

void Game::setScene(gui::GameScene* newScene)
{
    scene_ = newScene;
}

void Game::onObjectIndexChanged(const std::shared_ptr<MovingObject>& object, size_t index)
{
    const auto& cell     = map_->cell(index);
    const auto& modifier = cell.modifier();
    if (modifier && object == playerBomberman_) {
        auto bomberman = std::dynamic_pointer_cast<Bomberman>(object);
        modifier->activate(*bomberman);
        if (modifier->durationType() == ModifierDurationType::Temporary) {
            auto event = std::make_unique<ModifierDeactivationEvent>(bomberman, cell.modifier());
            timerQueue.addEvent(createDelay(modifier->duration()), std::move(event));
        }
        map_->setModifier(cell.index(), nullptr);
    }
}

void Game::addExplosionEvent(const std::shared_ptr<Bomb>& bomb)
{
    auto callback = std::bind(&Game::explodeBomb, this, std::placeholders::_1);
    timerQueue.addEvent(createDelay(bomb->explosionDelay), std::make_unique<BombExplosionEvent>(bomb, callback));
}

void Game::explodeBomb(const std::shared_ptr<Bomb>& bomb)
{
    auto  explosionData = bm::explodeBomb(*map_, *bomb);
    auto& explosion     = explosionData.explosion;
    emit  explosionHappened(explosion);
    auto  callback = std::bind(&Game::onExplosionFinished, this, std::placeholders::_1);
    qDebug() << "Adding event from explodeBomb";
    timerQueue.addEvent(createDelay(bomb->explosionPeriod),
                        std::make_unique<BombExplosionFinishedEvent>(explosion, callback));
    for (auto* affectedObject : explosionData.affectedObjects) {
        explosion->collideWith(*affectedObject, collider_);
    }

    playerBomberman_->decreaseActiveBombs();
}

void Game::onExplosionFinished(const std::shared_ptr<Explosion>& explosion)
{
    emit explosionFinished(explosion);
    map_->removeExplosion(explosion);
}

void Game::setPlayerBomberman(const std::shared_ptr<Bomberman>& newPlayerBomberman)
{
    playerBomberman_ = newPlayerBomberman;
}

} // namespace bm
