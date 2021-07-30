#ifndef BOT_H
#define BOT_H

#include "character.hpp"
#include "collider.hpp"

namespace bm {
class Bot : public Character
{
public:
    ACCEPT_COLLISION;
};
} // namespace bm

#endif // BOT_H
