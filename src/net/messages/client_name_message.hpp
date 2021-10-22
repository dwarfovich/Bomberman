#ifndef BM_BYTEARRAYMESSAGE_HPP
#define BM_BYTEARRAYMESSAGE_HPP

#include "byte_array_message.hpp"

#include <QByteArray>
#include <QString>

namespace bm {

class ClientNameMessage : public ByteArrayMessage<QString>
{
public:
    ClientNameMessage() = default;
    ClientNameMessage(const QString &name);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
};

} // namespace bm

#endif // BM_BYTEARRAYMESSAGE_HPP
