#ifndef BM_CHARACTERMOVEDMESSAGE_HPP
#define BM_CHARACTERMOVEDMESSAGE_HPP

#include "message.hpp"
#include "game/move_data.hpp"

#include <QByteArray>

namespace bm {
class MovingObject;

class CharacterMovedMessage : public Message
{
public:
    CharacterMovedMessage() = default;
    CharacterMovedMessage(const MovingObject &object);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    std::pair<uint8_t, MoveData> moveData() const;

private:
    QByteArray data_;
};

} // namespace bm

#endif // BM_CHARACTERMOVEDMESSAGE_HPP
