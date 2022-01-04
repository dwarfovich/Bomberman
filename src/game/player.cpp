#include "player.hpp"

#include <QDataStream>

namespace bm {

QDataStream& operator<<(QDataStream& stream, const Player& player)
{
    stream << player.name_;
    stream << player.campaignLevel_;
    stream << player.currentGameBombermanId_;

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Player& player)
{
    stream >> player.name_;
    stream >> player.campaignLevel_;
    stream >> player.currentGameBombermanId_;

    return stream;
}

Player::Player(const QString& filename) : filename_ { filename }
{}

const QString& Player::filename() const
{
    return filename_;
}

void Player::setFilename(const QString& newFilename)
{
    filename_ = newFilename;
}

const QString& Player::name() const
{
    return name_;
}

void Player::setName(const QString& newName)
{
    name_ = newName;
}

size_t Player::campaignLevel() const
{
    return campaignLevel_;
}

void Player::setCampaignLevel(size_t newCampaignLevel)
{
    campaignLevel_ = newCampaignLevel;
}

object_id_t Player::currentGameBombermanId() const
{
    return currentGameBombermanId_;
}

void Player::setCurrentGameBombermanId(object_id_t newCurrentGameBombermanId)
{
    currentGameBombermanId_ = newCurrentGameBombermanId;
}

} // namespace bm
