#ifndef BM_STARTGAMEMESSAGE_HPP
#define BM_STARTGAMEMESSAGE_HPP

#include "notifying_message.hpp"

namespace bm {

class StartGameMessage : public NotifyingMessage
{
public:
    // Message interface
public:
    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace bm

#endif // BM_STARTGAMEMESSAGE_HPP
