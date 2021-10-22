#include "single_player_game_process.hpp"
#include "game.hpp"
#include "map.hpp"

#include <QDebug>
#define DEB qDebug()

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
    if (character->id() == game_->playerId() && game_->map()->isExitActivated() && index == game_->map()->exitIndex()) {
        assignGameResultToGame(generateGameResult());
        changeGameStatus(GameStatus::GameOver);
    }
}

GameResult SinglePlayerGameProcess::generateGameResult()
{
    GameResult result;
    return result;
}

} // namespace bm
