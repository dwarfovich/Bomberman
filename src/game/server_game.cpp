#include "server_game.hpp"
#include "bomb_explosion.hpp"
#include "bomb_explosion_event.hpp"
#include "modifier_deactivation_event.hpp"

namespace bm {

ServerGame::ServerGame()
    : collider_{this}
{}

void ServerGame::start()
{
    moveTimer.start(updateTimeout_);
}

void ServerGame::movePlayer(size_t player, Direction direction)
{
    if (isCorrectPlayerIndex(player)) {
        bombermans_[player]->setSpeed(defaultBombermanSpeed);
        bombermans_[player]->setDirection(direction);
    }
}

void ServerGame::stopPlayer(size_t player)
{
    if (isCorrectPlayerIndex(player)) {
//        if (player1_->movementData().direction == direction) {
            bombermans_[player]->setSpeed(0);
//        }
    }
}

void ServerGame::placeBomb(size_t player)
{
    std::shared_ptr<Bomb> bomb = bombermans_[player]->createBomb();
    if (bomb) {
        auto index = map_->coordinatesToIndex(bombermans_[player]->movementData().coordinates);
        if (map_->isProperIndex(index)) {
            bomb->cellIndex = index;
            map_->placeBomb(bomb);
            addExplosionEvent(bomb);
        }
    }
}

bool ServerGame::isCorrectPlayerIndex(size_t index) const
{
    return (index < bombermans_.size());
}

void ServerGame::onObjectIndexChanged(const std::shared_ptr<MovingObject> &object, size_t index)
{
    const auto& cell     = map_->cell(index);
    const auto& modifier = cell.modifier();
    if (modifier && std::find(bombermans_.cbegin(), bombermans_.cend(), object) != bombermans_.cend()) {
        // TODO: Get rid of dynamic_cast
        auto bomberman = std::dynamic_pointer_cast<Bomberman>(object);
        modifier->activate(*bomberman);
        if (modifier->type() == ModifierType::Temporary) {
            auto event = std::make_unique<ModifierDeactivationEvent>(bomberman, cell.modifier());
            timerQueue.addEvent(createDelay(modifier->duration()), std::move(event));
        }
        map_->setModifier(cell.index(), nullptr);
    }
}

void ServerGame::addPlayer(const std::shared_ptr<Bomberman> &player)
{
    player->setId(bombermans_.size());
    bombermans_.push_back(player);
}

void ServerGame::addExplosionEvent(const std::shared_ptr<Bomb>& bomb)
{
    auto callback = std::bind(&ServerGame::explodeBomb, this, std::placeholders::_1);
    timerQueue.addEvent(createDelay(bomb->explosionDelay), std::make_unique<BombExplosionEvent>(bomb, callback));
}

void ServerGame::explodeBomb(const std::shared_ptr<Bomb>& bomb)
{
    auto  explosionData = bm::explodeBomb(*map_, *bomb);
    auto& explosion     = explosionData.explosion;
    for (auto* affectedObject : explosionData.affectedObjects) {
        explosion.collideWith(*affectedObject, collider_);
    }

    const auto& bomberman = bomb->owner;
    bomberman->decreaseActiveBombs();
}

void ServerGame::setMap(const std::shared_ptr<Map> &map)
{
    Game::setMap(map)    ;
    // TODO: Disconnect oldies.
    connect(&moveTimer, &QTimer::timeout, [this]() {
        map_->moveObjects(updateTimeout_);
    });
    connect(map_.get(), &Map::objectIndexChanged, this, &ServerGame::onObjectIndexChanged);
}

} // namespace bm



