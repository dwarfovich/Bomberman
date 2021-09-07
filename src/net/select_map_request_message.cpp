#include "select_map_request_message.hpp"
#include "i_message_visitor.hpp"
#include "message_maker.hpp"

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::SelectMapRequest, SelectMapRequestMessage);

SelectMapRequestMessage::SelectMapRequestMessage(QString mapFileName) : data_ { mapFileName.toUtf8() }
{}

MessageType SelectMapRequestMessage::type() const
{
    return MessageType::SelectMapRequest;
}

void SelectMapRequestMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int SelectMapRequestMessage::dataLength() const
{
    return data_.size();
}

void SelectMapRequestMessage::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

void SelectMapRequestMessage::fromStream(QDataStream &stream)
{
    stream >> data_;
}

QString SelectMapRequestMessage::toString() const
{
    return QString { data_ };
}
} // namespace bm
