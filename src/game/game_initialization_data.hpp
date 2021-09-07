#ifndef BM_GAMEINITIALIZATIONDATA_HPP
#define BM_GAMEINITIALIZATIONDATA_HPP

#include "game_object.hpp"

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
} // namespace gui

class GameInitializationData
{
public:
    std::unique_ptr<Game>                   game = nullptr;
    std::shared_ptr<Map>                    map;
    std::vector<std::shared_ptr<Bomberman>> bombermans;
    gui::GameScene*                         scene = nullptr;
    gui::GameView*                          view  = nullptr;
    QStringList                             errors;
};

} // namespace bm

#endif // BM_GAMEINITIALIZATIONDATA_HPP
