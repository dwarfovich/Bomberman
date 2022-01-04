#ifndef BM_NETWORKPLAYERGAMEOVERCONDITION_HPP
#define BM_NETWORKPLAYERGAMEOVERCONDITION_HPP

#include "game_over_condition.hpp"

namespace bm {

class NetworkPlayerGameOverCondition : public GameOverCondition
{
public:
    NetworkPlayerGameOverCondition();

    bool checkIfGameOver(const Game &game) override;
};

} // namespace bm

#endif // BM_NETWORKPLAYERGAMEOVERCONDITION_HPP
