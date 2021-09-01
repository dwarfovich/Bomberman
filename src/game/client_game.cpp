#include "client_game.hpp"
#include "net/client.hpp"
#include "net/character_moved_message.hpp"
#include "net/bomb_placed_message.hpp"
#include "net/cell_changed_message.hpp"

namespace bm {

ClientGame::ClientGame(Client *client) : client_ { client }
{
    client_->setParent(this);

    connect(client_, &Client::messageReceived, this, &ClientGame::onMessageReceived);
    connect(client_, &Client::readyToStartGame, this, &ClientGame::onReadyToStart);
}

void ClientGame::start()
{}

// void ClientGame::addPlayer(const std::shared_ptr<Bomberman> &player)
//{}

void ClientGame::movePlayer(object_id_t player, Direction direction)
{
    // TODO: Check if bombermans and playerBomberman_ have proper ids.
    playerBomberman_->setSpeed(bomberman_ns::defaultSpeed);
    playerBomberman_->setDirection(direction);
    CharacterMovedMessage message(*playerBomberman_);
    client_->sendMessage(message);
}

void ClientGame::stopPlayer(object_id_t player)
{
    playerBomberman_->setSpeed(0);
    CharacterMovedMessage message(*playerBomberman_);
    client_->sendMessage(message);
}

std::shared_ptr<Bomb> ClientGame::placeBomb(object_id_t player)
{
    std::shared_ptr<Bomb> bomb = playerBomberman_->createBomb();
    if (bomb) {
        auto index = map_->coordinatesToIndex(playerBomberman_->movementData().coordinates);
        if (map_->isProperIndex(index)) {
            bomb->cellIndex = index;
            map_->placeBomb(bomb);
            addExplosionEvent(bomb);
        }

        BombPlacedMessage message { *bomb };
        client_->sendMessage(message);
    }

    return bomb;
}

void ClientGame::onReadyToStart()
{
    // Game::start();
}

void ClientGame::onMessageReceived(const std::unique_ptr<Message> &message)
{
    message->accept(*this);
}

const std::shared_ptr<Bomberman> &ClientGame::bomberman(object_id_t playerId) const
{
    const auto &bombermans = map_->bombermans();
    auto        iter       = std::find_if(bombermans.cbegin(), bombermans.cend(), [playerId](const auto &iter) {
        return iter.second->id() == playerId;
    });
    if (iter != bombermans.cend()) {
        return iter->second;
    } else {
        const static std::shared_ptr<Bomberman> empty;
        return empty;
    }
}

void ClientGame::visit(const StartGameMessage &message)
{
    if (!moveTimer_.isActive()) {
        moveTimer_.start(42);
    }
}

void ClientGame::setMap(const std::shared_ptr<Map> &map)
{
    Game::setMap(map);
    connect(&moveTimer_, &QTimer::timeout, [this]() {
        map_->moveObjects(42);
    });

    playerBomberman_ = bomberman(client_->playerId());
}

object_id_t ClientGame::playerId() const
{
    return client_->playerId();
}

void ClientGame::visit(const CharacterMovedMessage &message)
{
    const auto &moveData = message.moveData();
    map_->moveCharacter(moveData.first, moveData.second);
}

void ClientGame::visit(const BombPlacedMessage &message)
{
    const auto &bomb = message.bomb();
    map_->placeBomb(bomb);
    addExplosionEvent(bomb);
}

void ClientGame::visit(const CellChangedMessage &message)
{
    const auto &cell = message.cell();
    map_->setCell(cell);
}

} // namespace bm
