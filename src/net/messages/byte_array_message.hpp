#ifndef BM_SIMPLEMESSAGE_HPP
#define BM_SIMPLEMESSAGE_HPP

#include "message.hpp"

#include <QByteArray>
#include <QDataStream>

namespace bm {

template<typename InputType>
class ByteArrayMessage : public Message
{
public:
    ByteArrayMessage() = default;
    ByteArrayMessage(const InputType &input);

    int  dataLength() const override;
    void dataToStream(QDataStream &stream) const override;
    void fromStream(QDataStream &stream) override;

    InputType payload() const;

private:
    QByteArray data_;
};

template<typename InputType>
ByteArrayMessage<InputType>::ByteArrayMessage(const InputType &input)
{
    QDataStream stream { &data_, QDataStream::WriteOnly };
    stream << input;
}

template<typename InputType>
int ByteArrayMessage<InputType>::dataLength() const
{
    return data_.size();
}

template<typename InputType>
void ByteArrayMessage<InputType>::dataToStream(QDataStream &stream) const
{
    stream << data_;
}

template<typename InputType>
void ByteArrayMessage<InputType>::fromStream(QDataStream &stream)
{
    stream >> data_;
}

template<typename InputType>
InputType ByteArrayMessage<InputType>::payload() const
{
    InputType   payload;
    QDataStream stream { data_ };
    stream >> payload;

    return payload;
}

} // namespace bm

#endif // BM_SIMPLEMESSAGE_HPP
