#ifndef BM_BOT_AI_HPP
#define BM_BOT_AI_HPP

#include "bot.hpp"

#include <memory>

namespace bm {
class Map;

class BotAi
{
public:
    BotAi(const Map& map, const Bot* bot);

    virtual Direction chooseNextDirection() const;

private:
    const Map& map_;
    const Bot* bot_;
};

} // namespace bm

#endif // BM_BOT_AI_HPP
