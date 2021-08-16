#include "game_factory.hpp"
#include "server_game.hpp"
#include "network_game.hpp"
#include "net/server.hpp"

namespace bm {

std::unique_ptr<Game> createSinglePlayerGame(const std::shared_ptr<Map> &map)
{
    auto game = std::make_unique<ServerGame>();

    return game;
}

std::unique_ptr<Game> createNetworkGame(Server *server, const std::shared_ptr<Map> &map)
{
    auto game = std::make_unique<NetworkGame>(server);
    game->setMap(map);

    return game;
}

} // namespace bm
