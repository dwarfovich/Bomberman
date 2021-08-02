#include "bot.hpp"
#include "bot_ai.hpp"
#include "bot_constants.hpp"

namespace bm {

Bot::Bot()
{
    setSpeed(botDefaultSpeed);
}

bool Bot::notifyIfMeetedWall() const
{
    return true;
}

void Bot::meetsWall()
{
    setDirection(ai_->chooseNextDirection());
}

void Bot::setAi(std::unique_ptr<BotAi> ai)
{
    ai_ = std::move(ai);
}

bool Bot::acceptsModifiers() const
{
    return false;
}

} // namespace bm
