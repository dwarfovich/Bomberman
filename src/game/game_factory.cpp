#include "game_factory.hpp"

#include "single_player_game.hpp"

namespace bm {

std::unique_ptr<Game> createSinglePlayerGame(const std::shared_ptr<Map> &map)
{
    auto game = std::make_unique<SinglePlayerGame>();

    return game;
}

} // namespace bm
