#include "bot_ai.hpp"

namespace bm {

BotAi::BotAi(const Map &map, const std::shared_ptr<Bot> &bot) : map_ { map }, bot_ { bot }
{}

} // namespace bm
