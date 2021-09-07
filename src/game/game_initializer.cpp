#include "game_initializer.hpp"
#include "game_initialization_data.hpp"
#include "map_loader.hpp"
#include "game.hpp"
#include "bot_factory.hpp"
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

    QObject::connect(gameData.game, &Game::cellChanged, scene, &gui::GameScene::cellChanged);
    QObject::connect(gameData.game, &Game::characterMoved, scene, &gui::GameScene::onCharacterMoved);
    QObject::connect(gameData.game, &Game::characterStartedMoving, scene, &gui::GameScene::onCharacterStartedMove);
    QObject::connect(gameData.game, &Game::characterStopped, scene, &gui::GameScene::onCharacterStopped);
    QObject::connect(gameData.game, &Game::bombPlaced, scene, &gui::GameScene::onBombPlaced);
    QObject::connect(gameData.game, &Game::bombExploded, scene, &gui::GameScene::onBombExploded);
    QObject::connect(gameData.game, &Game::explosionHappened, scene, &gui::GameScene::onExplosionHappened);
    QObject::connect(gameData.game, &Game::explosionFinished, scene, &gui::GameScene::onExplosionFinished);
    QObject::connect(gameData.game, &Game::objectDestroyed, scene, &gui::GameScene::onObjectDestroyed);

    gameData.game->setMap(gameData.mapData->map);

    return true;
}

QStringList initializeGame(const GameInitializationData& data)
{
    Q_ASSERT(data.game);
    Q_ASSERT(data.map);
    Q_ASSERT(data.scene);
    Q_ASSERT(data.view);

    QStringList errors;

    details::initializeBots(data, errors);
    details::initializeBombermans(data, errors);

    if (!errors.empty()) {
        return errors;
    }

    // TODO: May be set player's id here.
    // data.game->setPlayerBomberman(...)

    data.game->setMap(data.map);
    data.scene->setMap(data.map);
    data.view->setScene(data.scene);

    const auto* game = data.game.get();
    QObject::connect(game, &Game::cellChanged, data.scene, &gui::GameScene::cellChanged);
    QObject::connect(game, &Game::characterMoved, data.scene, &gui::GameScene::onCharacterMoved);
    QObject::connect(game, &Game::characterStartedMoving, data.scene, &gui::GameScene::onCharacterStartedMove);
    QObject::connect(game, &Game::characterStopped, data.scene, &gui::GameScene::onCharacterStopped);
    QObject::connect(game, &Game::bombPlaced, data.scene, &gui::GameScene::onBombPlaced);
    QObject::connect(game, &Game::bombExploded, data.scene, &gui::GameScene::onBombExploded);
    QObject::connect(game, &Game::explosionHappened, data.scene, &gui::GameScene::onExplosionHappened);
    QObject::connect(game, &Game::explosionFinished, data.scene, &gui::GameScene::onExplosionFinished);
    QObject::connect(game, &Game::objectDestroyed, data.scene, &gui::GameScene::onObjectDestroyed);

    return errors;
}

void details::initializeBots(const GameInitializationData& data, QStringList& errors)
{
    const auto& map         = data.map;
    const auto& botRespawns = map->respawnPlaces(RespawnType::Bot);
    for (auto respawn : botRespawns) {
        const std::shared_ptr<Bot>& bot = createBot(BotType::Regular, *map);
        bot->setCoordinates(map->indexToCellCenterCoordinates(respawn));
        if (bot) {
            map->addBot(bot);
        } else {
            errors << "Cann't create bot";
        }
    }
}

void details::initializeBombermans(const GameInitializationData& data, QStringList& errors)
{
    const auto& map               = data.map;
    const auto& bombermanRespawns = map->respawnPlaces(RespawnType::Bomberman);
    if (data.bombermans.size() <= bombermanRespawns.size()) {
        for (size_t i = 0; i < data.bombermans.size(); ++i) {
            const auto& bomberman = data.bombermans[i];
            bomberman->setCoordinates(map->indexToCellCenterCoordinates(bombermanRespawns[i]));
            map->addBomberman(bomberman);
        }
    } else {
        errors << "Not enough respawn plases for bombermans";
    }
}

} // namespace bm
