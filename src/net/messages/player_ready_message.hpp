#ifndef BM_MAPINITIALIZEDMESSAGE_HPP
#define BM_MAPINITIALIZEDMESSAGE_HPP

#include "byte_array_message.hpp"
#include "game/game_object_id.hpp"

namespace bm {

class PlayerReadyMessage : public ByteArrayMessage<object_id_t>
{
public:
    PlayerReadyMessage(object_id_t playerId = invalidObjectId);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace bm

#endif // BM_MAPINITIALIZEDMESSAGE_HPP
