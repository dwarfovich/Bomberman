#ifndef BM_MAPINITIALIZEDMESSAGE_HPP
#define BM_MAPINITIALIZEDMESSAGE_HPP

#include "notifying_message.hpp"

namespace bm {

class MapInitializedMessage : public NotifyingMessage
{
public:
    // Message interface
public:
    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace bm

#endif // BM_MAPINITIALIZEDMESSAGE_HPP
