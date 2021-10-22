#include "client_joining_game_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::ClientJoiningGame, ClientJoiningGameMessage);

MessageType ClientJoiningGameMessage::type() const
{
    return MessageType::ClientJoiningGame;
}

void ClientJoiningGameMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
