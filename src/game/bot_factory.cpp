#include "bot_factory.hpp"
#include "bot_ai.hpp"
#include "map.hpp"

namespace bm {

std::unique_ptr<Bot> createBot(BotType type, Map &map)
{
    if (type == BotType::Regular) {
        auto bot = std::make_unique<Bot>();
        bot->setAi(std::make_unique<BotAi>(map, bot.get(), map.randomSeed()));

        return bot;
    }

    assert(false);
    return nullptr;
}

} // namespace bm
