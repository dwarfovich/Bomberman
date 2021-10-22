#include "bot_ai.hpp"
#include "map.hpp"

#include <QRandomGenerator>

namespace bm {

BotAi::BotAi(Map& map, const Bot* bot, uint32_t seed)
    : map_ { map }, bot_ { bot }, seed_ { seed }, randomGenerator_ { std::make_unique<QRandomGenerator>(seed_) }
{}

Direction BotAi::chooseNextDirection() const
{
    std::array<Direction, 3> directions {};

    auto                 direction          = bot_->direction();
    static const uint8_t invalidDirection   = -1;
    uint8_t              nextValidDirection = invalidDirection;
    for (uint8_t checkedDirections = 0; checkedDirections < 3; ++checkedDirections) {
        direction = bm::nextDirection(direction);
        if (map_.nextCellIsMovable(*bot_, direction)) {
            directions[++nextValidDirection] = direction;
        }
    }

    if (nextValidDirection == invalidDirection) {
        return direction;
    } else {
        return directions[randomGenerator_->bounded(0, static_cast<int>(nextValidDirection + 1))];
    }
}

void BotAi::updateActivity()
{
    auto newMoveData      = bot_->movementData();
    auto newDirection     = chooseNextDirection();
    newMoveData.direction = newDirection;
    if ((newDirection == Direction::Upward || newDirection == Direction::Left) && newMoveData.speed > 0) {
        newMoveData.speed = -5;
    } else if ((newDirection == Direction::Downward || newDirection == Direction::Right)) {
        newMoveData.speed = 5;
    }
    map_.moveCharacter(bot_->id(), newMoveData);
}

} // namespace bm
