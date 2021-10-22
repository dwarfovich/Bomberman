#include "select_map_request_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::SelectMapRequest, SelectMapRequestMessage);

SelectMapRequestMessage::SelectMapRequestMessage(QString mapFileName) : ByteArrayMessage<QString> { mapFileName }
{}

MessageType SelectMapRequestMessage::type() const
{
    return MessageType::SelectMapRequest;
}

void SelectMapRequestMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
