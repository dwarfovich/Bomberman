#include "bot_ai.hpp"
#include "map.hpp"

#include <QRandomGenerator>

namespace bm {

BotAi::BotAi(const Map& map, const Bot* bot, uint32_t seed)
    : map_ { map }, bot_ { bot }, seed_ { seed }, randomGenerator_ { std::make_unique<QRandomGenerator>(seed_) }
{}

Direction BotAi::chooseNextDirection() const
{
    std::array<Direction, 3> directions {};

    auto   direction = bot_->direction();
    size_t count     = 0;
    for (; count < 3; ++count) {
        direction = bm::nextDirection(direction);
        if (map_.nextCellIsMovable(*bot_, direction)) {
            directions[count] = direction;
        }
    }

    return directions[randomGenerator_->bounded(0, static_cast<int>(count))];
}

} // namespace bm
