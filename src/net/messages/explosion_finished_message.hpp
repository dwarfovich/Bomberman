#ifndef BM_EXPLOSIONFINISHEDMESSAGE_HPP
#define BM_EXPLOSIONFINISHEDMESSAGE_HPP

#include "game/game_object.hpp"
#include "message.hpp"

namespace bm {

class ExplosionFinishedMessage : public Message
{
public:
    ExplosionFinishedMessage(object_id_t id = invalidId);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    object_id_t explosionId() const;

private:
    object_id_t explosionId_;
};

} // namespace bm

#endif // BM_EXPLOSIONFINISHEDMESSAGE_HPP
