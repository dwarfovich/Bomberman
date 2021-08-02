#include "bot_ai.hpp"
#include "map.hpp"

namespace bm {

BotAi::BotAi(const Map& map, const Bot* bot) : map_ { map }, bot_ { bot }
{}

Direction BotAi::nextDirection() const
{
    auto direction = bot_->direction();
    for (int i = 0; i < 3; ++i) {
        direction = bm::nextDirection(direction);
        if (map_.nextCellIsMovable(*bot_, direction)) {
            return direction;
        }
    }

    return direction;
}

} // namespace bm
