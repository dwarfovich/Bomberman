#ifndef BM_CLIENTIDMESSAGE_HPP
#define BM_CLIENTIDMESSAGE_HPP

#include "message.hpp"

namespace bm {

class ClientIdMessage : public Message
{
public:
    explicit ClientIdMessage(uint8_t playerId = 0xFF);

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

#endif // BM_CLIENTIDMESSAGE_HPP
