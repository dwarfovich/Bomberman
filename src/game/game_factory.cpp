#include "game_factory.hpp"
#include "game_initialization_data.hpp"
#include "server_game.hpp"
#include "network_game.hpp"
#include "client_game.hpp"
#include "map_loader.hpp"
#include "single_player_game_process.hpp"
#include "network_game_process_handler.hpp"
#include "net/server.hpp"
#include "net/client.hpp"

namespace bm {

namespace {
bool createBombermansForPlayers(const std::unordered_set<uint8_t>& playersIds, Map& map, NetworkGame& game)
{
    const auto& respawns = map.playerRespawns();
    if (respawns.size() < playersIds.size()) {
        return false;
    }

    size_t currentRespawn = 0;
    for (uint8_t id : playersIds) {
        auto bomberman = std::make_shared<Bomberman>();
        bomberman->setBombPrototype({});
        bomberman->setCoordinates(map.indexToCellCenterCoordinates(respawns[currentRespawn]));
        ++currentRespawn;
        map.addBomberman(bomberman);
        //        game.addPlayer(bomberman);
    }

    return true;
}
} // namespace

GameInitializationData createSinglePlayerGame(const std::shared_ptr<Map>& map)
{
    Q_ASSERT(map);

    GameInitializationData data;
    data.map              = map;
    data.game             = std::make_unique<ServerGame>();
    const auto& bomberman = std::make_shared<Bomberman>();
    data.bombermans.push_back(bomberman);
    data.playerBomberman = bomberman->id();
    data.game->setGameProcessHandler(std::make_unique<SinglePlayerGameProcess>());

    return data;
}

std::unique_ptr<Game> createClientGame(Client* client)
{
    auto game = std::make_unique<ClientGame>(client);
    game->setMap(client->initializedMap());

    return game;
}

std::unique_ptr<Game> createNetworkGame(Server* server)
{
    auto game = std::make_unique<NetworkGame>(server);
    game->setGameProcessHandler(std::make_unique<NetworkGameProcessHandler>());

    return game;
}

} // namespace bm
