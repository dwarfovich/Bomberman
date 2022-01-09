#ifndef BM_CLIENTIDMESSAGE_HPP
#define BM_CLIENTIDMESSAGE_HPP

#include "byte_array_message.hpp"
#include "game/game_object.hpp"

namespace bm {

// TODO: rename SetPlayerIdMessage to something like SetPlayerBombermanIdMessage.
class SetPlayerIdMessage : public ByteArrayMessage<object_id_t>
{
public:
    explicit SetPlayerIdMessage(object_id_t playerId = 0xFF);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace bm

#endif // BM_CLIENTIDMESSAGE_HPP
