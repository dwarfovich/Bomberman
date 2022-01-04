#include "network_game_process_handler.hpp"
#include "game.hpp"
#include "player.hpp"

namespace bm {

NetworkGameProcessHandler::NetworkGameProcessHandler()
{}

void NetworkGameProcessHandler::setGame(const std::shared_ptr<Game>& game)
{
    Q_ASSERT(game);
    connect(game.get(), &Game::characterDestroyed, this, &NetworkGameProcessHandler::onCharacterDestroyed);
    GameProcessHandler::setGame(game);
}

void NetworkGameProcessHandler::onCharacterDestroyed(const std::shared_ptr<Character>& character)
{
    if (character->type() != CharacterType::Bomberman) {
        return;
    }

    destroyedBombermans_.push_back(character->id());

    const auto& bombermans = game_->map()->bombermans();
    if (bombermans.empty() || bombermans.size() == 1) {
        assignGameResultToGame(generateGameResult());
        changeGameStatus(GameStatus::GameOver);
    }
}

GameResult NetworkGameProcessHandler::generateGameResult()
{
    GameResult  result;
    const auto& bombermans   = game_->map()->bombermans();
    result.characterIdsLoose = destroyedBombermans_;

    const auto& players = gamePlayers();
    for (const auto& destroyedBombermanId : destroyedBombermans_) {
        auto iter = std::find_if(players.cbegin(), players.cend(), [destroyedBombermanId](const auto& player) {
            return (player->currentGameBombermanId() == destroyedBombermanId);
        });
        if (iter != players.cend()) {
            result.losePlayers.push_back((*iter)->name());
            qDebug() << (*iter)->name();
        }
    }

    if (bombermans.empty()) {
        result.gameWon = false;
    } else {
        const auto& winner    = bombermans.begin()->first;
        result.characterIdWon = winner->id();
        result.gameWon        = true;
    }

    return result;
}

} // namespace bm
