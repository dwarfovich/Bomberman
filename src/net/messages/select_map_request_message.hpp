#ifndef BM_SELECTMAPREQUESTMESSAGE_HPP
#define BM_SELECTMAPREQUESTMESSAGE_HPP

#include "byte_array_message.hpp"

#include <QString>

namespace bm {

class SelectMapRequestMessage : public ByteArrayMessage<QString>
{
public:
    SelectMapRequestMessage(QString mapFileName = {});

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace bm

#endif // BM_SELECTMAPREQUESTMESSAGE_HPP
