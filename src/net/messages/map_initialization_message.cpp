#include "map_initialization_message.hpp"
#include "i_message_visitor.hpp"
#include "game/map.hpp"
#include "message_maker.hpp"

#include <QIODevice>

namespace bm {
namespace message_ns {

REGISTER_MESSAGE_MAKER(MessageType::MapInitialization, MapInitializationMessage);

MapInitializationMessage::MapInitializationMessage(const Map &map)
{
    setMap(map);
}

MessageType MapInitializationMessage::type() const
{
    return MessageType::MapInitialization;
}

void MapInitializationMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int MapInitializationMessage::dataLength() const
{
    return data_.size();
}

void MapInitializationMessage::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

void MapInitializationMessage::fromStream(QDataStream &stream)
{
    stream >> data_;
}

void MapInitializationMessage::setMap(const Map &map)
{
    data_.clear();
    QDataStream stream { &data_, QDataStream::WriteOnly };
    stream << map;
}

const QByteArray &MapInitializationMessage::data() const
{
    return data_;
}

} // namespace message_ns
} // namespace bm
