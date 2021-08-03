#ifndef BM_GAMEOVERCONDITION_HPP
#define BM_GAMEOVERCONDITION_HPP

#include "game_winner_type.hpp"

#include <memory>

namespace bm {
class Game;
class Bomberman;

class GameOverCondition
{
public:
    virtual bool checkIfGameOver(const Game& game) = 0;

    GameWinnerType winnerType() const;
    const std::shared_ptr<Bomberman> &winnerBomberman() const;

private:
    GameWinnerType winnerType_ = GameWinnerType::NoWinner;
    std::shared_ptr<Bomberman> winnerBomberman_ = nullptr;
};

} // namespace bm

#endif // BM_GAMEOVERCONDITION_HPP
