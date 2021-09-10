#ifndef BM_STARTGAMEMESSAGE_HPP
#define BM_STARTGAMEMESSAGE_HPP

#include "notifying_message.hpp"

namespace bm {
namespace message_ns {

class StartGameMessage : public NotifyingMessage
{
public:
    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace message_ns
} // namespace bm

#endif // BM_STARTGAMEMESSAGE_HPP
