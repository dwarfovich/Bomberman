#include "game_initializer.hpp"
#include "map_loader.hpp"
#include "game.hpp"
#include "gui/game_scene.hpp"
#include "gui/game_view.hpp"
#include "gui/character_graphics_item.hpp"
#include "gui/bot_graphics_item.hpp"

#include <QObject>

namespace bm {

bool initializeGame(const GameData& gameData)
{
    auto* scene = gameData.view->scene();
    scene->setMap(gameData.mapData->map);
    // scene->clear();

    // QObject::connect(gameData.mapData->map.get(), &Map::cellChanged, scene, &gui::GameScene::cellChanged);
    // QObject::connect(gameData.mapData->map.get(), &Map::objectMoved, scene, &gui::GameScene::onCharacterMoved);

    const auto& respawns = gameData.mapData->map->playerRespawns();

    const auto& map       = gameData.mapData->map;
    auto        bomberman = std::make_shared<Bomberman>();
    bomberman->setBombPrototype({});
    bomberman->setId(0);
    bomberman->setCoordinates(map->indexToCellCenterCoordinates(respawns[0]));
    map->addBomberman(bomberman);
    gameData.game->addPlayer(bomberman);
    gameData.game->setPlayerBomberman(bomberman);

    // const auto& player = gameData.mapData->bombermans[0];
    // gameData.game->addPlayer(player);
    // gameData.mapData->map->addBomberman(player);
    //    auto characterItem = std::make_unique<gui::CharacterGraphicsItem>();
    //    characterItem->setCharacter(bomberman);
    //    scene->addMovingObject(bomberman, std::move(characterItem));
    scene->addBomberman(bomberman);

    for (const auto& bot : gameData.mapData->bots) {
        //        gameData.mapData->map->addBot(bot);
        //        auto botItem = std::make_unique<gui::BotGraphicsItem>();
        //        botItem->setCharacter(bot);
        //        scene->addMovingObject(bot, std::move(botItem));
        gameData.mapData->map->addBot(bot);
        scene->addBot(bot);
    }

    QObject::connect(gameData.game, &Game::cellChanged, scene, &gui::GameScene::cellChanged);
    QObject::connect(gameData.game, &Game::objectMoved, scene, &gui::GameScene::onCharacterMoved);
    QObject::connect(gameData.game, &Game::characterStartedMoving, scene, &gui::GameScene::onCharacterStartedMove);
    QObject::connect(gameData.game, &Game::characterStopped, scene, &gui::GameScene::onCharacterStopped);
    QObject::connect(gameData.game, &Game::bombPlaced, scene, &gui::GameScene::onBombPlaced);
    QObject::connect(gameData.game, &Game::bombExploded, scene, &gui::GameScene::onBombExploded);
    QObject::connect(gameData.game, &Game::explosionHappened, scene, &gui::GameScene::onExplosionHappened);
    QObject::connect(gameData.game, &Game::explosionFinished, scene, &gui::GameScene::onExplosionFinished);
    QObject::connect(gameData.game, &Game::objectDestroyed, scene, &gui::GameScene::onObjectDestroyed);

    gameData.game->setMap(gameData.mapData->map);
    // gameData.view->setMap(gameData.mapData->map);
    gameData.game->setScene(scene);

    return true;
}

} // namespace bm
