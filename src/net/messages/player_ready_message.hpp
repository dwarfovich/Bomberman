#ifndef BM_MAPINITIALIZEDMESSAGE_HPP
#define BM_MAPINITIALIZEDMESSAGE_HPP

#include "game/game_object_id.hpp"
#include "message.hpp"

namespace bm {
namespace message_ns {

class PlayerReadyMessage : public Message
{
public:
    PlayerReadyMessage(object_id_t playerId = invalidObjectId);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    object_id_t playerId() const;

private:
    object_id_t playerId_;
};

} // namespace message_ns
} // namespace bm

#endif // BM_MAPINITIALIZEDMESSAGE_HPP
