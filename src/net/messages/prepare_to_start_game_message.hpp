#ifndef BM_PREPARETOSTARTGAMEMESSAGE_HPP
#define BM_PREPARETOSTARTGAMEMESSAGE_HPP

#include "notifying_message.hpp"

namespace bm {
namespace message_ns {

class PrepareToStartGameMessage : public NotifyingMessage
{
public:
    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace message_ns
} // namespace bm

#endif // BM_PREPARETOSTARTGAMEMESSAGE_HPP
