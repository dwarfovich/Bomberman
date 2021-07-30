#ifndef BOT_H
#define BOT_H

#include "character.hpp"
#include "collider.hpp"

namespace bm {
class BotAi;

class Bot : public Character
{
public:
    ACCEPT_COLLISION;

    bool notifyIfMeetedWall() const override;
    void meetsWall() override;

    void setAi(std::unique_ptr<BotAi> ai);

private:
    std::unique_ptr<BotAi> ai_;

};
} // namespace bm

#endif // BOT_H
