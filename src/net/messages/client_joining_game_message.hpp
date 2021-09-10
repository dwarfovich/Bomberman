#ifndef BM_CLIENTREADYMESSAGE_HPP
#define BM_CLIENTREADYMESSAGE_HPP

#include "message.hpp"
#include "notifying_message.hpp"
#include "message_type.hpp"

#include <cinttypes>

namespace bm {
namespace message_ns {

class ClientJoiningGameMessage : public NotifyingMessage
{
public:
    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace message_ns
} // namespace bm

#endif // BM_CLIENTREADYMESSAGE_HPP
