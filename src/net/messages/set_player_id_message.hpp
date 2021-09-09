#ifndef BM_CLIENTIDMESSAGE_HPP
#define BM_CLIENTIDMESSAGE_HPP

#include "message.hpp"
#include "game/game_object.hpp"

namespace bm {

class SetPlayerIdMessage : public Message
{
public:
    explicit SetPlayerIdMessage(object_id_t playerId = 0xFF);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    object_id_t playerId() const;

private:
    object_id_t playerId_;
};

} // namespace bm

#endif // BM_CLIENTIDMESSAGE_HPP
