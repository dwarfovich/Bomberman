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

    botsKilled_.clear();
    GameProcessHandler::setGame(game);
    const auto& map = game_->map();
    // TODO: consider connecting to game signals.
    connect(map.get(), &Map::characterDestroyed, this, &SinglePlayerGameProcess::onCharacterDestroyed);
    connect(map.get(), &Map::characterIndexChanged, this, &SinglePlayerGameProcess::onCharacterIndexChanged);
}

void SinglePlayerGameProcess::onCharacterDestroyed(const std::shared_ptr<Character>& character)
{
    if (character->type() == CharacterType::Bot) {
        botsKilled_.push_back(character->id());
        const auto& map = game_->map();
        if (map->bots().size() == 0) {
            map->activateExit();
        }
    } else {
        assignGameResultToGame(generateGameResult());
        changeGameStatus(GameStatus::GameOver);
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
    GameResult  result;
    const auto& map = game_->map();
    if (map->bots().empty()) {
        result.characterIdWon   = game_->playerId();
        result.characterTypeWon = CharacterType::Bomberman;
        result.gameWon          = true;
    } else {
        result.characterTypeWon = CharacterType::Bot;
        result.gameWon          = false;
    }
    result.characterIdsLoose = std::move(botsKilled_);

    return result;
}

} // namespace bm
