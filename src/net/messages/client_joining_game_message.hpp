#ifndef BM_CLIENTREADYMESSAGE_HPP
#define BM_CLIENTREADYMESSAGE_HPP

#include "message.hpp"
#include "byte_array_message.hpp"
#include "message_type.hpp"
#include "game/player.hpp"

namespace bm {

// TODO: Rename message to something like "SetPlayerData". Do not forget to rename all other corresponig entities.
class ClientJoiningGameMessage : public ByteArrayMessage<Player>
{
public:
    ClientJoiningGameMessage(const Player& player = {});

    MessageType type() const override;
    void        accept(IMessageVisitor& visitor) override;
};

} // namespace bm

#endif // BM_CLIENTREADYMESSAGE_HPP
