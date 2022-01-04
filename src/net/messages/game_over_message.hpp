#ifndef BM_GAMEOVERMESSAGE_HPP
#define BM_GAMEOVERMESSAGE_HPP

#include "byte_array_message.hpp"
#include "game/game_result.hpp"

namespace bm {

class GameOverMessage : public ByteArrayMessage<GameResult>
{
public:
    GameOverMessage(const GameResult& gameResult = {});

    MessageType type() const override;
    void        accept(IMessageVisitor& visitor) override;
};

} // namespace bm

#endif // BM_GAMEOVERMESSAGE_HPP
