#ifndef BM_GAMEUTILS_HPP
#define BM_GAMEUTILS_HPP

#include <QString>
#include <QFile>

#include <memory>
#include <vector>

namespace bm {
class Player;

namespace game_utils {

namespace details {
inline const QString playerFileExtension      = ".sav";
inline const QString playerFileFilter         = '*' + playerFileExtension;
inline const int     maxPlayerFilenameCounter = 100;
inline QString       playerFileFullPath(const QString& playersFolder, const QString& filename);
} // namespace details

std::vector<std::shared_ptr<Player>> loadPlayers(const QString& playersFolder);
bool                                 savePlayer(const Player& player, const QString& playersFolder);
QString                              generateFilenameForPlayer(const QString& name, const QString& playersFolder);

} // namespace game_utils
} // namespace bm

#endif // BM_GAMEUTILS_HPP
