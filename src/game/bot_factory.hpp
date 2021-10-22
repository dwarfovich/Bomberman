#ifndef BM_BOTFACTORY_HPP
#define BM_BOTFACTORY_HPP

#include "bot_type.hpp"
#include "bot.hpp"

#include <memory>

namespace bm {
class Map;

std::unique_ptr<Bot> createBot(BotType type, Map& map);

} // namespace bm

#endif // BM_BOTFACTORY_HPP
