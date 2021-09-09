#ifndef BM_MAPINITIALIZEDMESSAGE_HPP
#define BM_MAPINITIALIZEDMESSAGE_HPP

#include "game/game_object.hpp"
#include "message.hpp"

namespace bm {

class PlayerReadyMessage : public Message
{
public:
    PlayerReadyMessage(object_id_t playerId = invalidId);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

private:
    object_id_t playerId_;
};

} // namespace bm

#endif // BM_MAPINITIALIZEDMESSAGE_HPP
