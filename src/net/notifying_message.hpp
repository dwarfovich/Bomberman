#ifndef BM_NOTIFYINGMESSAGE_HPP
#define BM_NOTIFYINGMESSAGE_HPP

#include "message.hpp"

namespace bm {

class NotifyingMessage : public Message
{
public:
    int  dataLength() const override;
    void dataToStream(QDataStream &stream) const override;
    void fromStream(QDataStream &stream) override;
};

} // namespace bm

#endif // BM_NOTIFYINGMESSAGE_HPP
