#include "game_over_message.hpp"
#include "message_type.hpp"
#include "message_maker.hpp"
#include "i_message_visitor.hpp"

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::GameOver, GameOverMessage);

GameOverMessage::GameOverMessage(const GameResult &gameResult) : ByteArrayMessage<GameResult> { gameResult }
{}

MessageType GameOverMessage::type() const
{
    return MessageType::GameOver;
}

void GameOverMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

} // namespace bm
