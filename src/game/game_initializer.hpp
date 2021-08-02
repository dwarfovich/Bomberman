#ifndef BM_GAMEINITIALIZER_HPP
#define BM_GAMEINITIALIZER_HPP

namespace bm {
namespace map_loader {
struct MapData;
}
class Game;
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

bool initializeGame(const GameData& gameData);

} // namespace bm

#endif // BM_GAMEINITIALIZER_HPP
