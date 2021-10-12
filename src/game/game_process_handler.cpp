#include "game_process_handler.hpp"
#include "game.hpp"

namespace bm {

void GameProcessHandler::setGame(const std::shared_ptr<Game>& game)
{
    game_ = game;
}

void GameProcessHandler::changeGameStatus(GameStatus newStatus)
{
    game_->setGameStatus(newStatus);
}

} // namespace bm