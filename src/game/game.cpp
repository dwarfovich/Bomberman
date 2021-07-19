#include "game.hpp"
#include "time.hpp"
#include "bomb_explosion_event.hpp"
#include "modifier_deactivation_event.hpp"
#include "map_constants.hpp"
#include "gui/game_scene.hpp"

#include <functional>

namespace bm {
Game::Game() : explosionProcessor { *this }
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
    if (map_) {
        disconnect(map_.get(), &Map::bombermanIndexChanged, this, &Game::onBombermanIndexChanged);
    }
    map_ = map;
    connect(map_.get(), &Map::bombermanIndexChanged, this, &Game::onBombermanIndexChanged);
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
        auto index = map_->coordinatesToIndex(player->moveData.coordinates);
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
    connect(map_.get(), &Map::cellChanged, scene_, &gui::GameScene::cellChanged);
}

void Game::onBombermanIndexChanged(const std::shared_ptr<Bomberman>& bomberman, size_t index)
{
    const auto& cell     = map_->cell(index);
    const auto& modifier = cell.modifier;
    if (modifier) {
        modifier->activate(*bomberman);
        if (modifier->type() == ModifierType::Temporary) {
            auto event = std::make_unique<ModifierDeactivationEvent>(bomberman, cell.modifier);
            timerQueue.addEvent(createDelay(modifier->duration()), std::move(event));
        }
        map_->setModifier(cell.index, nullptr);
    }
}

void Game::addExplosionEvent(const std::shared_ptr<Bomb>& bomb)
{
    auto callback = std::bind(&Game::explodeBomb, this, std::placeholders::_1);
    timerQueue.addEvent(createDelay(bomb->explosionDelay), std::make_unique<BombExplosionEvent>(bomb, callback));
}

void Game::explodeBomb(const std::shared_ptr<Bomb>& bomb)
{
    qDebug() << "Game::explodeBomb";
    explosionProcessor.setBomb(bomb);
    auto affectedObjects = map_->explodeBomb(bomb);
    qDebug() << "exploded objects:" << affectedObjects.size();
    for (auto* object : affectedObjects) {
        object->explode(explosionProcessor);
    }

    const auto& bomberman = bomb->owner;
    bomberman->decreaseActiveBombs();
}

} // namespace bm
