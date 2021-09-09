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

// int ClientJoiningGameMessage::dataLength() const
//{
//    return 1;
//}

// void ClientJoiningGameMessage::dataToStream(QDataStream &stream) const
//{
//    stream << playerId_;
//}

// void ClientJoiningGameMessage::fromStream(QDataStream &stream)
//{
//    stream >> playerId_;
//}

// uint8_t ClientJoiningGameMessage::playerId() const
//{
//    return playerId_;
//}

} // namespace bm
