#include "client_joining_game_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

#include <QDataStream>

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::ClientJoiningGame, ClientJoiningGameMessage);

ClientJoiningGameMessage::ClientJoiningGameMessage(const Player &player) : ByteArrayMessage<Player> { player }
{}

MessageType ClientJoiningGameMessage::type() const
{
    return MessageType::ClientJoiningGame;
}

void ClientJoiningGameMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
