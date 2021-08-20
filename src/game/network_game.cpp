#include "network_game.hpp"
#include "net/server.hpp"
#include "net/client_ready_message.hpp"
#include "net/map_initialization_message.hpp"

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
    ServerGame::start();
}

} // namespace bm
