#include "map_initialized_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::MapInitialized, MapInitializedMessage);

MessageType MapInitializedMessage::type() const
{
    return MessageType::MapInitialized;
}

void MapInitializedMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
