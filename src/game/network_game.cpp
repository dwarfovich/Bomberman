#include "network_game.hpp"
#include "net/server.hpp"
#include "net/messages/player_ready_message.hpp"
#include "net/messages/map_initialization_message.hpp"
#include "net/messages/start_game_message.hpp"
#include "net/messages/character_moved_message.hpp"
#include "net/messages/bomb_placed_message.hpp"
#include "net/messages/cell_changed_message.hpp"
#include "net/messages/set_player_id_message.hpp"
//#include "net/messages/map_initialized_message.hpp"

namespace bm {

NetworkGame::NetworkGame(Server *server) : server_ { server }
{
    server->setParent(this);

    auto bomberman = std::make_shared<Bomberman>();
    playersBombermans_.push_back(bomberman);
    playerId_ = bomberman->id();
    playersPreparingToStartGame_.insert(bomberman->id());

    connect(server_, &Server::messageReceived, this, &NetworkGame::onMessageReceived);
    connect(server_, &Server::reallyReadyToStartGame, this, &NetworkGame::startGame);
}

void NetworkGame::start()
{
    prepareToStart();
}

void NetworkGame::prepareToStart()
{
    setGameStatus(GameStatus::Preparing);
    playersReady_.insert(playerId());

    if (playersReady_ == playersPreparingToStartGame_) {
        StartGameMessage startMessage;
        server_->broadcastMessage(startMessage);
        setGameStatus(GameStatus::Playing);
        ServerGame::start();
    }
}

void NetworkGame::setMap(const std::shared_ptr<Map> &map)
{
    ServerGame::setMap(map);
    makeConnections();
    connect(map.get(), &Map::cellStructureChanged, this, &NetworkGame::onMapCellChanged);
}

void NetworkGame::onMessageReceived(const std::unique_ptr<Message> &message)
{
    message->accept(*this);
}

void NetworkGame::onMapCellChanged(size_t index)
{
    const auto &       cell = map_->cell(index);
    CellChangedMessage message { cell };
    server_->broadcastMessage(message);
}

void NetworkGame::makeConnections()
{
    connectionsMade_ = true;
}

void NetworkGame::sendMapInitializationMessage()
{
    MapInitializationMessage message { *map_ };
    server_->broadcastMessage(message);
}

void NetworkGame::startGame()
{
    StartGameMessage message;
    server_->broadcastMessage(message);
    ServerGame::start();
}

const std::vector<std::shared_ptr<Bomberman>> &NetworkGame::playersBombermans() const
{
    return playersBombermans_;
}

void NetworkGame::movePlayer(object_id_t player, Direction direction)
{
    auto bomberman = map_->bomberman(player);
    if (bomberman) {
        CharacterMovedMessage message(*bomberman);
        server_->broadcastMessage(message);
        ServerGame::movePlayer(player, direction);
    }
}

void NetworkGame::stopPlayer(object_id_t player)
{
    auto bomberman = map_->bomberman(player);
    if (bomberman) {
        CharacterMovedMessage message(*bomberman);
        server_->broadcastMessage(message);
        ServerGame::stopPlayer(player);
    }
}

std::shared_ptr<Bomb> NetworkGame::placeBomb(object_id_t player)
{
    const auto &bomb = ServerGame::placeBomb(player);
    if (bomb) {
        BombPlacedMessage message { *bomb };
        server_->broadcastMessage(message);
    }

    return bomb;
}

void NetworkGame::visit(const CharacterMovedMessage &message)
{
    const auto &moveData = message.moveData();
    map_->moveCharacter(moveData.first, moveData.second);
    server_->broadcastMessage(message, server_->currentMessageClient());
}

void NetworkGame::visit(const BombPlacedMessage &message)
{
    const auto &bomb = message.bomb();
    map_->placeBomb(bomb);
    server_->broadcastMessage(message, server_->currentMessageClient());
}

void NetworkGame::visit(const ClientJoiningGameMessage &message)
{
    if (currentStatus() == GameStatus::Waiting) {
        auto bomberman = std::make_shared<Bomberman>();
        playersPreparingToStartGame_.insert(bomberman->id());
        playersBombermans_.push_back(bomberman);

        SetPlayerIdMessage idMessage(bomberman->id());
        server_->sendMessage(idMessage, server_->currentMessageClient());
        emit server_->logMessageRequest("Adding bomberman for client ");
    }
}

void NetworkGame::visit(const PlayerReadyMessage &message)
{
    if (playersReady_ == playersPreparingToStartGame_) {
        StartGameMessage startMessage;
        server_->broadcastMessage(startMessage);
        setGameStatus(GameStatus::Playing);
        ServerGame::start();
    }
}

} // namespace bm
