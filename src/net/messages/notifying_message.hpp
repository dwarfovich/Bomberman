#ifndef BM_NOTIFYINGMESSAGE_HPP
#define BM_NOTIFYINGMESSAGE_HPP

#include "message.hpp"

namespace bm {
namespace message_ns {

class NotifyingMessage : public Message
{
public:
    int  dataLength() const override;
    void dataToStream(QDataStream &stream) const override;
    void fromStream(QDataStream &stream) override;
};

} // namespace message_ns
} // namespace bm

#endif // BM_NOTIFYINGMESSAGE_HPP
