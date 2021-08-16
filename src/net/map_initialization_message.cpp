#include "map_initialization_message.hpp"
#include "i_message_visitor.hpp"
#include "game/map.hpp"

namespace bm {

MapInitializationMessage::MapInitializationMessage(const Map &map)
{
    QDataStream stream { data_ };
    stream << map;
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

} // namespace bm
