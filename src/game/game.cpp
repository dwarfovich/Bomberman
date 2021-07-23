#include "game.hpp"
#include "time.hpp"
#include "bomb_explosion_event.hpp"
#include "modifier_deactivation_event.hpp"
#include "map_constants.hpp"
#include "bomb_explosion.hpp"

#include "gui/game_scene.hpp"
#include "gui/character_graphics_item.hpp"

#include <functional>

namespace bm {
Game::Game() : explosionProcessor { *this }
{}

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
    connect(map_.get(), &Map::cellChanged, scene_, &gui::GameScene::cellChanged);

    // moveProcessor_ = std::make_unique<MoveProcessor>(*map);
    connect(map_.get(), &Map::objectIndexChanged, this, &Game::onObjectIndexChanged);
    connect(map_.get(), &Map::characterMoved, scene_, &gui::GameScene::characterMoved);
    connect(&moveTimer, &QTimer::timeout, [this]() {
        map_->moveObjects(timeout_);
    });
}
void Game::setPlayer(const std::shared_ptr<Bomberman>& player)
{
    player_            = player;
    auto characterItem = std::make_unique<gui::CharacterGraphicsItem>();
    characterItem->setCharacter(player);
    map_->addMovingObject(player);
    // moveProcessor_->addObject(player);
    scene_->addCharacter(player, std::move(characterItem));
}

bool Game::movePlayer(Direction direction)
{
    player_->setSpeed(defaultBombermanSpeed);
    // character->moveData.speed     = defaultBombermanSpeed;
    // character->moveData.direction = direction;
    player_->setDirection(direction);
    if (direction == Direction::Left || direction == Direction::Upward) {
        if (player_->speed() > 0) {
            player_->setSpeed(player_->speed() * -1);
        }
    } else {
        // character->moveData.speed = abs(character->moveData.speed);
    }
    // character->
    // character->location += coordinatesShift(direction);
    // emit characterMoved(character);
    return true;
}

void Game::stopPlayer(Direction direction)
{
    if (player_->movementData().direction == direction) {
        player_->setSpeed(0);
    }
}

void Game::placeBomb()
{
    // const auto&           player = map_->player();
    std::shared_ptr<Bomb> bomb = player_->createBomb();
    if (bomb) {
        auto index = map_->coordinatesToIndex(player_->movementData().coordinates);
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
    const auto& modifier = cell.modifier;
    if (modifier && object == player_) {
        auto bomberman = std::dynamic_pointer_cast<Bomberman>(object);
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
    auto result = bm::explodeBomb(*map_, *bomb);
    //    auto affectedObjects = map_->removeBomb(bomb);
    //    qDebug() << "exploded objects:" << affectedObjects.size();
    //    for (auto* object : affectedObjects) {
    //        object->explode(explosionProcessor);
    //    }

    const auto& bomberman = bomb->owner;
    bomberman->decreaseActiveBombs();
}

} // namespace bm
