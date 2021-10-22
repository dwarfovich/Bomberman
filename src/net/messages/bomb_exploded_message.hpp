#ifndef BM_BOMBEXPLODEDMESSAGE_HPP
#define BM_BOMBEXPLODEDMESSAGE_HPP

#include "message.hpp"

#include <QByteArray>

#include <memory>

namespace bm {
class Bomb;
class Explosion;

class BombExplodedMessage : public Message
{
public:
    BombExplodedMessage() = default;
    BombExplodedMessage(const Bomb &bomb, const Explosion &explosion);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    std::pair<std::shared_ptr<Bomb>, std::shared_ptr<Explosion>> result() const;

private:
    QByteArray data_;
};

} // namespace bm

#endif // BM_BOMBEXPLODEDMESSAGE_HPP
