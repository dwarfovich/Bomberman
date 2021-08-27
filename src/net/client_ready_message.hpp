#ifndef BM_CLIENTREADYMESSAGE_HPP
#define BM_CLIENTREADYMESSAGE_HPP

#include "message.hpp"
#include "message_type.hpp"

#include <cinttypes>

namespace bm {

class ClientReadyMessage : public Message
{
public:
    ClientReadyMessage(uint8_t playerId = 0);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    uint8_t playerId() const;

private:
    uint8_t playerId_;
};

} // namespace bm

#endif // BM_CLIENTREADYMESSAGE_HPP
