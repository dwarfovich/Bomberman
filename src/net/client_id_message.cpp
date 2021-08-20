#include "client_id_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::ClientId, ClientIdMessage);

ClientIdMessage::ClientIdMessage(uint8_t playerId) : playerId_ { playerId }
{}

MessageType ClientIdMessage::type() const
{
    return MessageType::ClientId;
}

void ClientIdMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int ClientIdMessage::dataLength() const
{
    return 1;
}

void ClientIdMessage::dataToStream(QDataStream &stream) const
{
    stream << playerId_;
}

void ClientIdMessage::fromStream(QDataStream &stream)
{
    stream >> playerId_;
}

uint8_t ClientIdMessage::playerId() const
{
    return playerId_;
}

} // namespace bm
