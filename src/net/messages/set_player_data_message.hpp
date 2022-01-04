#ifndef BM_SETPLAYERDATAMESSAGE_HPP
#define BM_SETPLAYERDATAMESSAGE_HPP

#include "byte_array_message.hpp"
#include "game/player.hpp"

namespace bm {

class SetPlayerDataMessage : public ByteArrayMessage<Player>
{
public:
    SetPlayerDataMessage();
};

} // namespace bm

#endif // BM_SETPLAYERDATAMESSAGE_HPP
