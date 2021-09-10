#include "client_name_message.hpp"
#include "message_type.hpp"
#include "message_maker.hpp"
#include "i_message_visitor.hpp"

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::ClientName, ClientNameMessage);

ClientNameMessage::ClientNameMessage(const QString &name) : ByteArrayMessage<QString> { name }
{}

MessageType ClientNameMessage::type() const
{
    return MessageType::ClientName;
}

void ClientNameMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
