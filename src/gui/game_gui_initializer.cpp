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

    // TODO: I've added Qt::UniqueConnection to prevent duplicates, so consider to get rid of data.sceneConnectedToGame var.
    if (!data.sceneConnectedToGame) {
        const auto* game = data.game.get();
        QObject::connect(game, &Game::cellStructureChanged, data.scene, &gui::GameScene::onCellStructureChanged,Qt::UniqueConnection);
        QObject::connect(game, &Game::characterMoved, data.scene, &gui::GameScene::onCharacterMoved,Qt::UniqueConnection);
        QObject::connect(game, &Game::characterStartedMoving, data.scene, &gui::GameScene::onCharacterStartedMove,Qt::UniqueConnection);
        QObject::connect(game, &Game::characterStopped, data.scene, &gui::GameScene::onCharacterStopped,Qt::UniqueConnection);
        QObject::connect(game, &Game::bombPlaced, data.scene, &gui::GameScene::onBombPlaced,Qt::UniqueConnection);
        QObject::connect(game, &Game::bombExploded, data.scene, &gui::GameScene::onBombExploded,Qt::UniqueConnection);
        QObject::connect(game, &Game::explosionHappened, data.scene, &gui::GameScene::onExplosionHappened,Qt::UniqueConnection);
        QObject::connect(game, &Game::explosionFinished, data.scene, &gui::GameScene::onExplosionFinished,Qt::UniqueConnection);
        QObject::connect(game, &Game::objectDestroyed, data.scene, &gui::GameScene::onObjectDestroyed,Qt::UniqueConnection);
        QObject::connect(game, &Game::modifierAdded, data.scene, &gui::GameScene::onModifierAdded,Qt::UniqueConnection);
        QObject::connect(game, &Game::modifierRemoved, data.scene, &gui::GameScene::onModifierRemoved,Qt::UniqueConnection);
        QObject::connect(game, &Game::exitRevealed, data.scene, &gui::GameScene::onExitRevealed,Qt::UniqueConnection);
        QObject::connect(game, &Game::exitActivated, data.scene, &gui::GameScene::onExitActivated,Qt::UniqueConnection);
        QObject::connect(game, &Game::gameStatusChanged, data.mainWindow, &gui::MainWindow::gameStatusChanged, Qt::UniqueConnection);

        data.sceneConnectedToGame = true;
    }
    return true;
}

} // namespace gui
} // namespace bm
