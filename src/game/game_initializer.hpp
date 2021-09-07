#ifndef BM_GAMEINITIALIZER_HPP
#define BM_GAMEINITIALIZER_HPP

#include <QStringList>

namespace bm {

namespace map_loader {
struct MapData;
}

class Game;
class GameInitializationData;

namespace gui {
class GameScene;
class GameView;
} // namespace gui

struct GameData
{
    Game*                game    = nullptr;
    map_loader::MapData* mapData = nullptr;
    gui::GameView*       view    = nullptr;
};

bool        initializeGame(const GameData& gameData);
QStringList initializeGame(const GameInitializationData& data);

namespace details {
void initializeBots(const GameInitializationData& data, QStringList& errors);
void initializeBombermans(const GameInitializationData& data, QStringList& errors);
} // namespace details

} // namespace bm

#endif // BM_GAMEINITIALIZER_HPP
