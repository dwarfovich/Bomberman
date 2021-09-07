#include "game_initializer.hpp"
#include "map_loader.hpp"
#include "game.hpp"
#include "gui/game_scene.hpp"
#include "gui/game_view.hpp"

#include <QObject>

namespace bm {

bool initializeGame(const GameData& gameData)
{
    auto* scene = gameData.view->scene();
    scene->setMap(gameData.mapData->map);
    const auto& respawns = gameData.mapData->map->playerRespawns();

    const auto& map       = gameData.mapData->map;
    auto        bomberman = std::make_shared<Bomberman>();
    bomberman->setBombPrototype({});
    bomberman->setCoordinates(map->indexToCellCenterCoordinates(respawns[0]));
    map->addBomberman(bomberman);
    gameData.game->setPlayerBomberman(bomberman->id());
    scene->addBomberman(bomberman);

    for (const auto& bot : gameData.mapData->bots) {
        gameData.mapData->map->addBot(bot);
        scene->addBot(bot);
    }

    QObject::connect(gameData.game, &Game::cellStructureChanged, scene, &gui::GameScene::onCellChanged);
    QObject::connect(gameData.game, &Game::characterMoved, scene, &gui::GameScene::onCharacterMoved);
    QObject::connect(gameData.game, &Game::characterStartedMoving, scene, &gui::GameScene::onCharacterStartedMove);
    QObject::connect(gameData.game, &Game::characterStopped, scene, &gui::GameScene::onCharacterStopped);
    QObject::connect(gameData.game, &Game::bombPlaced, scene, &gui::GameScene::onBombPlaced);
    QObject::connect(gameData.game, &Game::bombExploded, scene, &gui::GameScene::onBombExploded);
    QObject::connect(gameData.game, &Game::explosionHappened, scene, &gui::GameScene::onExplosionHappened);
    QObject::connect(gameData.game, &Game::explosionFinished, scene, &gui::GameScene::onExplosionFinished);
    QObject::connect(gameData.game, &Game::objectDestroyed, scene, &gui::GameScene::onObjectDestroyed);
    QObject::connect(gameData.game, &Game::modifierAdded, scene, &gui::GameScene::onModifierAdded);
    QObject::connect(gameData.game, &Game::modifierRemoved, scene, &gui::GameScene::onModifierRemoved);

    gameData.game->setMap(gameData.mapData->map);

    return true;
}

} // namespace bm
