#include "game_factory.hpp"
#include "server_game.hpp"
#include "network_game.hpp"
#include "net/server.hpp"

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
        bomberman->setPlayerId(id);
        bomberman->setCoordinates(map.indexToCellCenterCoordinates(respawns[currentRespawn]));
        ++currentRespawn;
        map.addBomberman(bomberman);
        game.addPlayer(bomberman);
    }

    return true;
}
} // namespace

std::unique_ptr<Game> createSinglePlayerGame(const std::shared_ptr<Map>& map)
{
    auto game = std::make_unique<ServerGame>();

    return game;
}

std::unique_ptr<Game> createNetworkGame(Server* server, const std::shared_ptr<Map>& map)
{
    auto        game       = std::make_unique<NetworkGame>(server);
    const auto& playersIds = server->playersIds();

    bool success = createBombermansForPlayers(playersIds, *map, *game);
    if (!success) {
        return nullptr;
    }

    game->setMap(map);
    game->startPreparing();

    return game;
}

} // namespace bm
