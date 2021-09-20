#ifndef BM_PLAYER_HPP
#define BM_PLAYER_HPP

#include <QString>

QT_BEGIN_NAMESPACE
class QDataStream;
QT_END_NAMESPACE

namespace bm {

class Player
{
public:
    friend QDataStream& operator<<(QDataStream& stream, const Player& player);
    friend QDataStream& operator>>(QDataStream& stream, Player& player);

    Player(const QString& filename = {});

    const QString& filename() const;
    void           setFilename(const QString& newFilename);

    const QString& name() const;
    void           setName(const QString& newName);

private:
    QString name_;
    QString filename_;
};

} // namespace bm

#endif // BM_PLAYER_HPP
