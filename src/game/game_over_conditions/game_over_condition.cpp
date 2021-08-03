#include "game_over_condition.hpp"

namespace bm {

GameWinnerType GameOverCondition::winnerType() const
{
    return winnerType_;
}

const std::shared_ptr<Bomberman> &GameOverCondition::winnerBomberman() const
{
    return winnerBomberman_;
}

} // namespace bm
