#ifndef BM_SINGLEPLAYERGAMEOVERCONDITION_HPP
#define BM_SINGLEPLAYERGAMEOVERCONDITION_HPP

#include "game_over_condition.hpp"

namespace bm {

class SinglePlayerGameOverCondition : public GameOverCondition
{
public:
    bool checkIfGameOver(const Game &game) override;
};

} // namespace bm

#endif // BM_SINGLEPLAYERGAMEOVERCONDITION_HPP
