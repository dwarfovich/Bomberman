#include "game.hpp"
#include "gui/game_scene.hpp"

#include <QDebug>

namespace bm {
Game::Game()
{
    connect(&timer_, &QTimer::timeout, [this]() {
        map_->moveObjects(timeout_);
    });
}

void Game::start()
{
    if (!scene_) {
        return;
    }
    timer_.start(timeout_);
}

void Game::setMap(const std::shared_ptr<Map>& map)
{
    map_ = map;
}

bool Game::movePlayer(Direction direction)
{
    const auto& player = map_->player();
    return map_->moveCharacter(player, direction);
    //    if (map_->canMoveCharacter(*player, direction)) {
    //        return true;
    //    } else {
    //        return false;
    //    }
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
        }
    }
}

void Game::setScene(gui::GameScene* newScene)
{
    scene_ = newScene;
    connect(map_.get(), &Map::cellChanged, scene_, &gui::GameScene::cellChanged);
}

} // namespace bm
