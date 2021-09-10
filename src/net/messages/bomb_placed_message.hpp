#ifndef BM_BOMBPLACEDMESSAGE_HPP
#define BM_BOMBPLACEDMESSAGE_HPP

#include "message.hpp"

#include <QByteArray>

namespace bm {
class Bomb;

namespace message_ns {
class BombPlacedMessage : public Message
{
public:
    BombPlacedMessage() = default;
    BombPlacedMessage(const Bomb &bomb);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    std::shared_ptr<Bomb> bomb() const;

private:
    QByteArray data_;
};

} // namespace message_ns
} // namespace bm

#endif // BM_BOMBPLACEDMESSAGE_HPP
