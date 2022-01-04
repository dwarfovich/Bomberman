#ifndef BM_PLAYER_HPP
#define BM_PLAYER_HPP

#include "game_object_id.hpp"

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

    size_t campaignLevel() const;
    void   setCampaignLevel(size_t newCampaignLevel);

    object_id_t currentGameBombermanId() const;
    void        setCurrentGameBombermanId(object_id_t newCurrentGameBombermanId);

private:
    QString     name_;
    QString     filename_;
    size_t      campaignLevel_ = 0;
    object_id_t currentGameBombermanId_;
};

} // namespace bm

#endif // BM_PLAYER_HPP
