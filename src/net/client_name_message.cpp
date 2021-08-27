#include "client_name_message.hpp"
#include "message_type.hpp"
#include "message_maker.hpp"
#include "i_message_visitor.hpp"

namespace bm {

REGISTER_MESSAGE_MAKER(MessageType::ClientName, ClientNameMessage);

ClientNameMessage::ClientNameMessage(const QString &name) : data_ { name.toUtf8() }
{}

MessageType ClientNameMessage::type() const
{
    return MessageType::ClientName;
}

void ClientNameMessage::accept(IMessageVisitor &visitor)
{
    visitor.visit(*this);
}

int ClientNameMessage::dataLength() const
{
    return data_.size();
}

void ClientNameMessage::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

void ClientNameMessage::fromStream(QDataStream &stream)
{
    stream >> data_;
}

void ClientNameMessage::setName(const QString &name)
{
    data_ = name.toUtf8();
}

QString ClientNameMessage::toString() const
{
    return QString::fromUtf8(data_);
}

} // namespace bm
