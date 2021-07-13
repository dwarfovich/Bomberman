#include "game.hpp"
#include "time.hpp"
#include "bomb_explosion_event.hpp"
#include "gui/game_scene.hpp"

#include <functional>

namespace bm {
Game::Game()
{
    connect(&moveTimer, &QTimer::timeout, [this]() {
        map_->moveObjects(timeout_);
    });
}

void Game::start()
{
    if (!scene_) {
        return;
    }
    moveTimer.start(timeout_);
}

void Game::setMap(const std::shared_ptr<Map>& map)
{
    map_ = map;
}

bool Game::movePlayer(Direction direction)
{
    const auto& player = map_->player();
    return map_->moveCharacter(player, direction);
}

void Game::stopPlayer(Direction direction)
{
    const auto& player = map_->player();
    map_->stopCharacter(player, direction);
}

void Game::placeBomb()
{
    const auto&           player = map_->player();
    std::shared_ptr<Bomb> bomb   = player->createBomb();
    if (bomb) {
        auto index = map_->coordinatesToIndex(player->moveData.location);
        if (index != wrongIndex) {
            bomb->cellIndex = index;
            map_->placeBomb(bomb);
            auto callback = std::bind(&Game::explodeBomb, this, std::placeholders::_1);
            timerQueue.addEvent(createDelay(bomb->explosionDelay), std::make_unique<BombExplosionEvent>(bomb, callback));
        }
    }
}

void Game::setScene(gui::GameScene* newScene)
{
    scene_ = newScene;
    connect(map_.get(), &Map::cellChanged, scene_, &gui::GameScene::cellChanged);
}

void Game::explodeBomb(const std::shared_ptr<Bomb> &bomb)
{
    qDebug() << "Game::explodeBomb";
    map_->explodeBomb(bomb);

    const auto& bomberman = bomb->owner;
    bomberman->decreaseActiveBombs();
}

} // namespace bm
