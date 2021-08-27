#ifndef BM_MAPINITIALIZATIONMESSAGE_HPP
#define BM_MAPINITIALIZATIONMESSAGE_HPP

#include "game/map.hpp"
#include "message.hpp"
#include "message_type.hpp"

#include <QByteArray>

namespace bm {

class MapInitializationMessage : public Message
{
public:
    MapInitializationMessage(const Map &map = {});

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    void              setMap(const Map &map);
    const QByteArray &data() const;

private:
    QByteArray data_;
};

} // namespace bm

#endif // BM_MAPINITIALIZATIONMESSAGE_HPP
