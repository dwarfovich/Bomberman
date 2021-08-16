#ifndef BM_MAPINITIALIZATIONMESSAGE_HPP
#define BM_MAPINITIALIZATIONMESSAGE_HPP

#include "message.hpp"
#include "message_type.hpp"

#include <QByteArray>

namespace bm {
class Map;

class MapInitializationMessage : public Message
{
public:
    MapInitializationMessage(const Map &map);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

private:
    QByteArray data_;
};

} // namespace bm

#endif // BM_MAPINITIALIZATIONMESSAGE_HPP
