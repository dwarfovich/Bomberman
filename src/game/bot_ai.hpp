#ifndef BM_BOT_AI_HPP
#define BM_BOT_AI_HPP

#include "bot.hpp"

#include <QRandomGenerator>

#include <memory>

namespace bm {
class Map;

class BotAi
{
public:
    BotAi(const Map& map, const Bot* bot, uint32_t seed = 0);

    virtual Direction chooseNextDirection() const;

private:
    const Map&                        map_;
    const Bot*                        bot_;
    uint32_t                          seed_;
    std::unique_ptr<QRandomGenerator> randomGenerator_;
};

} // namespace bm

#endif // BM_BOT_AI_HPP
