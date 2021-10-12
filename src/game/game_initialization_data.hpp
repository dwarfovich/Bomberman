#ifndef BM_GAMEINITIALIZATIONDATA_HPP
#define BM_GAMEINITIALIZATIONDATA_HPP

#include "game_object_id.hpp"
#include <QStringList>

#include <memory>
#include <vector>

namespace bm {
class Game;
class Bomberman;
class Map;

namespace gui {
class GameScene;
class GameView;
class MainWindow;
class PlayerKeyControls;
} // namespace gui

class GameInitializationData
{
public:
    std::shared_ptr<Game>                   game = nullptr;
    std::shared_ptr<Map>                    map;
    std::vector<std::shared_ptr<Bomberman>> bombermans;
    object_id_t                             playerBomberman      = invalidObjectId;
    bool                                    sceneConnectedToGame = false;
    gui::GameScene*                         scene                = nullptr;
    gui::GameView*                          view                 = nullptr;
    gui::MainWindow*                        mainWindow           = nullptr;
    gui::PlayerKeyControls*                 keyControls          = nullptr;
    QStringList                             errors;
};

} // namespace bm

#endif // BM_GAMEINITIALIZATIONDATA_HPP
