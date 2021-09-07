#ifndef BM_GAMEFACTORY_HPP
#define BM_GAMEFACTORY_HPP

#include "game.hpp"
#include "game_initialization_data.hpp"

#include <memory>

namespace bm {
class Server;
class Client;
namespace map_loader {
struct MapData;

}

GameInitializationData createSinglePlayerGame(const std::shared_ptr<Map>& map);
std::unique_ptr<Game>  createNetworkGame(Server*                     server,
                                         const std::shared_ptr<Map>& map,
                                         const map_loader::MapData&  mapData);
std::unique_ptr<Game>  createClientGame(Client* client);

} // namespace bm

#endif // BM_GAMEFACTORY_HPP
