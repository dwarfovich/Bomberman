#ifndef BM_CLIENTNAMEMESSAGE_HPP
#define BM_CLIENTNAMEMESSAGE_HPP

#include "message.hpp"

#include <QByteArray>
#include <QString>

namespace bm {

class ClientNameMessage : public Message
{
public:
    ClientNameMessage(const QString &name = {});

    MessageType type() const override;
    void        accept(IMessageVisitor &visitor) override;
    int         dataLength() const override;
    void        dataToStream(QDataStream &stream) const override;
    void        fromStream(QDataStream &stream) override;

    void    setName(const QString &name);
    QString toString() const;

private:
    QByteArray data_;
};

} // namespace bm

#endif // BM_CLIENTNAMEMESSAGE_HPP
