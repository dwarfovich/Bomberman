#ifndef BM_CHARACTERMOVEDMESSAGE_HPP
#define BM_CHARACTERMOVEDMESSAGE_HPP

#include "message.hpp"

#include <QByteArray>

namespace bm {
class MovingObject;

class CharacterMovedMessage : public Message
{
public:
    CharacterMovedMessage(const MovingObject &object);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

private:
    QByteArray data_;
};

} // namespace bm

#endif // BM_CHARACTERMOVEDMESSAGE_HPP
