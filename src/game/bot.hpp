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

    Bot();

    ObjectType type() const override;
    void       toStream(QDataStream &stream) const override;
    bool       notifyIfMeetedWall() const override;
    void       meetsWall() override;
    bool       acceptsModifiers() const override;

    void setAi(std::unique_ptr<BotAi> ai);

private:
    std::unique_ptr<BotAi> ai_;
};
} // namespace bm

#endif // BOT_H
