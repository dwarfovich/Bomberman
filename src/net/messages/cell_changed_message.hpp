#ifndef BM_CELLCHANGEDMESSAGE_HPP
#define BM_CELLCHANGEDMESSAGE_HPP

#include "message.hpp"

#include <QByteArray>

namespace bm {
class Cell;

class CellChangedMessage : public Message
{
public:
    CellChangedMessage() = default;
    CellChangedMessage(const Cell &cell);

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    Cell cell() const;

private:
    QByteArray data_;
};

} // namespace bm

#endif // BM_CELLCHANGEDMESSAGE_HPP
