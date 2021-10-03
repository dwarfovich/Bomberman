#ifndef GAME_TYPE_HPP
#define GAME_TYPE_HPP

#include <cinttypes>

namespace bm {

enum class GameType : uint8_t
{
    Fast,
    Campaign,
    Server,
    Client
};

}

#endif // GAME_TYPE_HPP
