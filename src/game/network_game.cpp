#include "network_game.hpp"
#include "net/server.hpp"
#include "net/client_ready_message.hpp"
#include "net/map_initialization_message.hpp"
#include "net/start_game_message.hpp"

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
}

void NetworkGame::onMessageReceived(const std::unique_ptr<Message> &message)
{
    message->accept(*this);
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

} // namespace bm
