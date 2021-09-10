#include "cell_changed_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"
#include "game/cell.hpp"

#include <QDataStream>

namespace bm {
namespace message_ns {

REGISTER_MESSAGE_MAKER(MessageType::CellChanged, CellChangedMessage);

CellChangedMessage::CellChangedMessage(const Cell &cell)
{
    QDataStream stream { &data_, QDataStream::WriteOnly };
    stream << cell;
}

MessageType CellChangedMessage::type() const
{
    return MessageType::CellChanged;
}

void CellChangedMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int CellChangedMessage::dataLength() const
{
    return data_.size();
}

void CellChangedMessage::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

void CellChangedMessage::fromStream(QDataStream &stream)
{
    stream >> data_;
}

Cell CellChangedMessage::cell() const
{
    Cell        cell;
    QDataStream stream { data_ };
    stream >> cell;

    return cell;
}

} // namespace message_ns
} // namespace bm
