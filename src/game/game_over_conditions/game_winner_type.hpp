#ifndef GAME_WINNER_TYPE_HPP
#define GAME_WINNER_TYPE_HPP

#include <cinttypes>

namespace bm {

enum class GameWinnerType : uint8_t {
    InProgress,
    Withdraw,
    Player,
    Bot,
};

}
#endif // GAME_WINNER_TYPE_HPP
