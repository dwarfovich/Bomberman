#ifndef BM_GAMESTATUS_HPP
#define BM_GAMESTATUS_HPP

#include <cinttypes>

namespace bm {

enum class GameStatus : uint8_t
{
    Waiting,
    Preparing,
    PreparingFinished,
    Playing,
    GameOver
};
} // namespace bm

#endif // BM_GAMESTATUS_HPP
