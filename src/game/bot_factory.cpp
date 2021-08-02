#include "bot_factory.hpp"
#include "bot_ai.hpp"

namespace bm {

std::unique_ptr<Bot> createBot(BotType type, const Map& map)
{
    if (type == BotType::Regular) {
        auto bot = std::make_unique<Bot>();
        bot->setAi(std::make_unique<BotAi>(map, bot.get()));

        return bot;
    }

    assert(false);
    return nullptr;
}

} // namespace bm
