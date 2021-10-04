#include "single_player_game_process.hpp"
#include "game.hpp"
#include "map.hpp"

namespace bm {

SinglePlayerGameProcess::SinglePlayerGameProcess()
{}

void SinglePlayerGameProcess::setGame(const std::shared_ptr<Game>& game)
{
    Q_ASSERT(game);
    Q_ASSERT(game->map());

    GameProcessHandler::setGame(game);
    const auto& map = game_->map();
    connect(map.get(), &Map::botRemoved, this, &SinglePlayerGameProcess::onBotRemoved);
    connect(map.get(), &Map::characterIndexChanged, this, &SinglePlayerGameProcess::onCharacterIndexChanged);
}

void SinglePlayerGameProcess::onBotRemoved()
{
    const auto& map = game_->map();
    if (map->bots().empty()) {
        map->activateExit();
    }
}

void SinglePlayerGameProcess::onCharacterIndexChanged(const std::shared_ptr<Character>& character, size_t index)
{
    if (character->id() == game_->playerId() && game_->map()->isExitActivated()) {
        changeGameStatus(GameStatus::GameOver);
    }
}

} // namespace bm
