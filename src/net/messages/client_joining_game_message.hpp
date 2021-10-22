#ifndef BM_CLIENTREADYMESSAGE_HPP
#define BM_CLIENTREADYMESSAGE_HPP

#include "message.hpp"
#include "notifying_message.hpp"
#include "message_type.hpp"

#include <cinttypes>

namespace bm {

class ClientJoiningGameMessage : public NotifyingMessage
{
public:
    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace bm

#endif // BM_CLIENTREADYMESSAGE_HPP
