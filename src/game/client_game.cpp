#include "client_game.hpp"
#include "game/player.hpp"
#include "net/client.hpp"
#include "net/messages/character_moved_message.hpp"
#include "net/messages/bomb_placed_message.hpp"
#include "net/messages/cell_changed_message.hpp"
#include "net/messages/map_initialization_message.hpp"
#include "net/messages/player_ready_message.hpp"
#include "net/messages/bomb_exploded_message.hpp"
#include "net/messages/explosion_finished_message.hpp"
#include "net/messages/client_joining_game_message.hpp"
#include "net/messages/game_over_message.hpp"

#include <QDebug>
#include <QMessageBox>

namespace bm {

ClientGame::ClientGame(Client *client) : client_ { client }
{
    client_->setParent(this);

    connect(client_, &Client::messageReceived, this, &ClientGame::onMessageReceived);
}

void ClientGame::reset()
{
    setGameStatus(GameStatus::Waiting);
}

void ClientGame::start()
{}

void ClientGame::movePlayer(object_id_t player, Direction direction)
{
    auto bomberman = map_->character(player);
    if (bomberman) {
        bomberman->setSpeed(bomberman_ns::defaultSpeed);
        bomberman->setDirection(direction);
        emit characterStartedMoving(bomberman);

        CharacterMovedMessage message(*bomberman);
        client_->sendMessage(message);
    }
}

void ClientGame::stopPlayer(object_id_t player)
{
    auto bomberman = map_->character(player);
    if (bomberman) {
        bomberman->setSpeed(0);
        emit characterStopped(bomberman);

        CharacterMovedMessage message(*bomberman);
        client_->sendMessage(message);
    }
}

std::shared_ptr<Bomb> ClientGame::placeBomb(object_id_t player)
{
    auto bomberman = map_->bomberman(player);
    if (bomberman && bomberman->canCreateBomb()) {
        std::shared_ptr<Bomb> bomb = bomberman->createBomb();
        bomb->cellIndex            = map_->coordinatesToIndex(bomberman->coordinates());
        BombPlacedMessage message { *bomb };
        client_->sendMessage(message);
        return bomb;
    } else {
        static const std::shared_ptr<Bomb> empty;
        return empty;
    }
}

void ClientGame::onMessageReceived(const std::unique_ptr<Message> &message)
{
    message->accept(*this);
}

void ClientGame::visit(const StartGameMessage &message)
{
    Game::start();
}

void ClientGame::visit(const CharacterMovedMessage &message)
{
    const auto &[characterId, moveData] = message.moveData();
    const auto &character               = map_->character(characterId);
    if (character) {
        character->setSpeed(moveData.speed);
        character->setDirection(moveData.direction);
        if (moveData.speed == 0) {
            emit characterStopped(character);
        } else {
            emit characterStartedMoving(character);
        }
    }
}

void ClientGame::visit(const BombPlacedMessage &message)
{
    const auto &bomb = message.bomb();
    map_->placeBomb(bomb);
    emit bombPlaced(bomb);
}

void ClientGame::visit(const CellChangedMessage &message)
{
    const auto &cell = message.cell();
    map_->setCell(cell);
}

void ClientGame::visit(const BombExplodedMessage &message)
{
    const auto &[bomb, explosion] = message.result();
    const auto &removedBomb       = map_->removeBomb(bomb->cellIndex);
    if (removedBomb) {
        emit        bombExploded(removedBomb);
        const auto &owner = bomberman(removedBomb->ownerId);
        if (owner) {
            owner->decreaseActiveBombs();
        }
    }
    map_->addExplosion(explosion);
    emit explosionHappened(explosion);
}

void ClientGame::visit(const MapInitializationMessage &message)
{
    auto        map = std::make_shared<Map>();
    QDataStream stream(message.data());
    stream >> *map;
    setMap(map);

    setGameStatus(GameStatus::PreparingFinished);
    PlayerReadyMessage readyMessage { playerId() };
    client_->sendMessage(readyMessage);
}

void ClientGame::visit(const SetPlayerIdMessage &message)
{
    playerId_ = message.payload();
    setGameStatus(GameStatus::Preparing);
    emit client_->logMessage("Set game status to Preparing");
    if (players_.size() > 0) {
        players_.front()->setCurrentGameBombermanId(playerId_);
        emit client_->logMessage("Setting player ID to " + QString::number(playerId_));
    } else {
        emit client_->logMessage("No player for setting bombreman ID");
    }
}

void ClientGame::visit(const ExplosionFinishedMessage &message)
{
    map_->removeExplosion(message.payload());
}

void ClientGame::visit(const ClientJoiningGameMessage &message)
{
    bool        playerFound       = false;
    const auto &playerFromMessage = message.payload();
    for (const auto &player : players_) {
        if (player->currentGameBombermanId() == playerFromMessage.currentGameBombermanId()) {
            *player     = playerFromMessage;
            playerFound = true;
        }
    }

    if (!playerFound) {
        auto newPlayer = std::make_shared<Player>(playerFromMessage);
        addPlayer(newPlayer);
    }
}

void ClientGame::visit(const GameOverMessage &message)
{
    gameResult_ = message.payload();
    setGameStatus(GameStatus::GameOver);
}

void ClientGame::setMap(const std::shared_ptr<Map> &map)
{
    if (map_) {
        disconnect(map_.get(), &Map::explosionRemoved, this, &Game::explosionFinished);
    }
    Game::setMap(map);
    connect(map_.get(), &Map::explosionRemoved, this, &Game::explosionFinished);
}

} // namespace bm
