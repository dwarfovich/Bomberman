#ifndef BM_SELECTMAPREQUESTMESSAGE_HPP
#define BM_SELECTMAPREQUESTMESSAGE_HPP

#include "message.hpp"

#include <QByteArray>
#include <QString>

namespace bm {

class SelectMapRequestMessage : public Message
{
public:
    SelectMapRequestMessage(QString mapFileName = {});

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    QString toString() const;

private:
    QByteArray data_;
};

} // namespace bm

#endif // BM_SELECTMAPREQUESTMESSAGE_HPP
