#include "bot.hpp"
#include "bot_ai.hpp"

namespace bm {

bool Bot::notifyIfMeetedWall() const
{
    return true;
}

void Bot::meetsWall()
{
    setDirection(ai_->nextDirection());
}

void Bot::setAi(std::unique_ptr<BotAi> ai)
{
    ai_ = std::move(ai);
}

}
