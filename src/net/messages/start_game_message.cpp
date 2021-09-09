#include "start_game_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::StartGame, StartGameMessage);

MessageType StartGameMessage::type() const
{
    return MessageType::StartGame;
}

void StartGameMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
