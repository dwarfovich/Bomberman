#include "game_gui_initializer.hpp"
#include "game/game_initialization_data.hpp"
#include "game/game.hpp"
#include "game_scene.hpp"
#include "game_view.hpp"
#include "main_window.hpp"
#include "player_key_controls.hpp"

namespace bm {
namespace gui {

bool initializeGameGui(GameInitializationData& data)
{
    Q_ASSERT(data.game);
    Q_ASSERT(data.map);
    Q_ASSERT(data.scene);
    Q_ASSERT(data.view);

    data.keyControls->playerId = data.game->playerId();

    data.scene->setMap(data.map);
    data.view->setScene(data.scene);

    if (!data.sceneConnectedToGame) {
        const auto* game = data.game.get();
        QObject::connect(game, &Game::cellStructureChanged, data.scene, &gui::GameScene::onCellStructureChanged);
        QObject::connect(game, &Game::characterMoved, data.scene, &gui::GameScene::onCharacterMoved);
        QObject::connect(game, &Game::characterStartedMoving, data.scene, &gui::GameScene::onCharacterStartedMove);
        QObject::connect(game, &Game::characterStopped, data.scene, &gui::GameScene::onCharacterStopped);
        QObject::connect(game, &Game::bombPlaced, data.scene, &gui::GameScene::onBombPlaced);
        QObject::connect(game, &Game::bombExploded, data.scene, &gui::GameScene::onBombExploded);
        QObject::connect(game, &Game::explosionHappened, data.scene, &gui::GameScene::onExplosionHappened);
        QObject::connect(game, &Game::explosionFinished, data.scene, &gui::GameScene::onExplosionFinished);
        QObject::connect(game, &Game::objectDestroyed, data.scene, &gui::GameScene::onObjectDestroyed);
        QObject::connect(game, &Game::modifierAdded, data.scene, &gui::GameScene::onModifierAdded);
        QObject::connect(game, &Game::modifierRemoved, data.scene, &gui::GameScene::onModifierRemoved);
        QObject::connect(game, &Game::exitRevealed, data.scene, &gui::GameScene::onExitRevealed);
        QObject::connect(game, &Game::exitActivated, data.scene, &gui::GameScene::onExitActivated);
        QObject::connect(game, &Game::gameStatusChanged, data.mainWindow, &gui::MainWindow::gameStatusChanged);

        data.sceneConnectedToGame = true;
    }
    return true;
}

} // namespace gui
} // namespace bm
