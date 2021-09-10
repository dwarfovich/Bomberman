#include "bot.hpp"
#include "bot_ai.hpp"

namespace bm {

Bot::Bot()
{
    setSpeed(bot_ns::defaultSpeed);
}

bool Bot::notifyIfMeetedWall() const
{
    return true;
}

void Bot::meetsWall()
{
    // setDirection(ai_->chooseNextDirection());
    ai_->updateActivity();
}

void Bot::setAi(std::unique_ptr<BotAi> ai)
{
    ai_ = std::move(ai);
}

bool Bot::acceptsModifiers() const
{
    return false;
}

CharacterType Bot::type() const
{
    return CharacterType::Bot;
}

void Bot::toStream(QDataStream &stream) const
{}

void Bot::fromStream(QDataStream &stream)
{}

} // namespace bm
