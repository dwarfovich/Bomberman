#include "client_ready_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::ClientReady, ClientReadyMessage);

ClientReadyMessage::ClientReadyMessage(uint8_t playerId) : playerId_ { playerId }
{}

MessageType ClientReadyMessage::type() const
{
    return MessageType::ClientReady;
}

void ClientReadyMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int ClientReadyMessage::dataLength() const
{
    return 1;
}

void ClientReadyMessage::dataToStream(QDataStream &stream) const
{
    stream << playerId_;
}

void ClientReadyMessage::fromStream(QDataStream &stream)
{
    stream >> playerId_;
}

uint8_t ClientReadyMessage::playerId() const
{
    return playerId_;
}

} // namespace bm
