#ifndef BM_BOT_AI_HPP
#define BM_BOT_AI_HPP

#include "bot.hpp"

namespace bm {
class Map;

class BotAi
{
public:
    BotAi(const Map& map, const std::shared_ptr<Bot>& bot);

private:
    const Map&           map_;
    std::shared_ptr<Bot> bot_;
};

} // namespace bm

#endif // BM_BOT_AI_HPP
