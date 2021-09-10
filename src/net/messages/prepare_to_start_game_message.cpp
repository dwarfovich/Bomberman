#include "prepare_to_start_game_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

namespace bm {
namespace message_ns {

REGISTER_MESSAGE_MAKER(MessageType::PrepareToStartGame, PrepareToStartGameMessage);

MessageType PrepareToStartGameMessage::type() const
{
    return MessageType::PrepareToStartGame;
}

void PrepareToStartGameMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace message_ns
} // namespace bm
