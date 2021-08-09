#include "game_factory.hpp"

#include "server_game.hpp"

namespace bm {

std::unique_ptr<Game> createSinglePlayerGame(const std::shared_ptr<Map> &map)
{
    auto game = std::make_unique<ServerGame>();

    return game;
}

} // namespace bm
