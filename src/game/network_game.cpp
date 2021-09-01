#include "network_game.hpp"
#include "net/server.hpp"
#include "net/client_ready_message.hpp"
#include "net/map_initialization_message.hpp"
#include "net/start_game_message.hpp"
#include "net/character_moved_message.hpp"
#include "net/bomb_placed_message.hpp"
#include "net/cell_changed_message.hpp"

namespace bm {

NetworkGame::NetworkGame(Server *server, QObject *parent) : ServerGame { parent }, server_ { server }
{
    server->setParent(this);

    connect(server_, &Server::messageReceived, this, &NetworkGame::onMessageReceived);
    connect(server_, &Server::reallyReadyToStartGame, this, &NetworkGame::startGame);
}

void NetworkGame::start()
{
    // ServerGame::start();
}

void NetworkGame::startPreparing()
{
    // createBombermansForPlayers();
    sendMapInitializationMessage();
    //    const auto &playerBomberman = map_->bombermans().at(0);
    //    setPlayerBomberman(playerBomberman);
    playerBomberman_ = bomberman(0);
}

void NetworkGame::setMap(const std::shared_ptr<Map> &map)
{
    ServerGame::setMap(map);
    makeConnections();
    connect(map.get(), &Map::cellChanged, this, &NetworkGame::onMapCellChanged);
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

// TODO: Change type of player to uint8_t or whatever it should be.
void NetworkGame::movePlayer(size_t player, Direction direction)
{
    ServerGame::movePlayer(player, direction);
    CharacterMovedMessage message(*bomberman(player));
    server_->broadcastMessage(message);
    ServerGame::movePlayer(player, direction);
}

void NetworkGame::stopPlayer(size_t player)
{
    ServerGame::stopPlayer(player);
    CharacterMovedMessage message(*bomberman(player));
    server_->broadcastMessage(message);
    ServerGame::stopPlayer(player);
}

std::shared_ptr<Bomb> NetworkGame::placeBomb(size_t player)
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
    // const auto &moveData = message.moveData();
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

} // namespace bm
