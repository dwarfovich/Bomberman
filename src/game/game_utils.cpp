#include "game_utils.hpp"
#include "player.hpp"

#include <QDir>
#include <QDataStream>

namespace bm {
namespace game_utils {

std::vector<std::shared_ptr<Player>> loadPlayers(const QString &playersFolder)
{
    QDir                                 playersDir { playersFolder };
    const auto &                         playerFiles = playersDir.entryList({ details::playerFileFilter }, QDir::Files);
    std::vector<std::shared_ptr<Player>> players;
    for (const auto &playerFile : playerFiles) {
        QFile file { playersDir.filePath(playerFile) };
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream stream { &file };
            auto        player = std::make_shared<Player>(playerFile);
            stream >> *player;
            players.push_back(std::move(player));
        }
    }

    return players;
}

bool savePlayer(const Player &player, const QString &playersFolder)
{
    // TODO: create `players` folder, if it doesn't exist, or you will not be able to create a file.
    QFile file { player.filename() };
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream stream { &file };
        stream << player;
        return true;
    } else {
        return false;
    }
}

QString generateFilenameForPlayer(const QString &name, const QString &playersFolder)
{
    using details::playerFileFullPath;
    if (QFile::exists(playerFileFullPath(playersFolder, name + details::playerFileExtension))) {
        for (int i = 1; i <= details::maxPlayerFilenameCounter; ++i) {
            const auto &filename = name + QString::number(i) + details::playerFileExtension;
            if (!QFile::exists(playerFileFullPath(playersFolder, filename))) {
                return filename;
            }
        }
    } else {
        return name + details::playerFileExtension;
    }

    return {};
}

QString details::playerFileFullPath(const QString &playersFolder, const QString &filename)
{
    if (playersFolder.endsWith(QDir::separator())) {
        return playersFolder + filename;
    } else {
        return playersFolder + QDir::separator() + filename;
    }
}

} // namespace game_utils

} // namespace bm
