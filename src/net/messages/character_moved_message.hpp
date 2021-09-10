#ifndef BM_CHARACTERMOVEDMESSAGE_HPP
#define BM_CHARACTERMOVEDMESSAGE_HPP

#include "game/game_object.hpp"

#include "message.hpp"
#include "game/move_data.hpp"

#include <QByteArray>

namespace bm {
class Character;

namespace message_ns {
class CharacterMovedMessage : public Message
{
public:
    CharacterMovedMessage() = default;
    CharacterMovedMessage(const Character &character);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    std::pair<object_id_t, MoveData> moveData() const;

private:
    QByteArray data_;
};

} // namespace message_ns
} // namespace bm

#endif // BM_CHARACTERMOVEDMESSAGE_HPP
