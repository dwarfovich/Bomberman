#ifndef BM_EXPLOSIONFINISHEDMESSAGE_HPP
#define BM_EXPLOSIONFINISHEDMESSAGE_HPP

#include "byte_array_message.hpp"
#include "game/game_object_id.hpp"

namespace bm {

class ExplosionFinishedMessage : public ByteArrayMessage<object_id_t>
{
public:
    ExplosionFinishedMessage(object_id_t id = invalidObjectId);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace bm

#endif // BM_EXPLOSIONFINISHEDMESSAGE_HPP
