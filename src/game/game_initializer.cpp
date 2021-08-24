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
    // scene->clear();

    QObject::connect(gameData.mapData->map.get(), &Map::cellChanged, scene, &gui::GameScene::cellChanged);
    QObject::connect(gameData.mapData->map.get(), &Map::objectMoved, scene, &gui::GameScene::onCharacterMoved);

    if (gameData.mapData->bombermans.size() < 1) {
        return false;
    }

    const auto& player = gameData.mapData->bombermans[0];
    gameData.game->addPlayer(player);
    gameData.mapData->map->addBomberman(player);
    auto characterItem = std::make_unique<gui::CharacterGraphicsItem>();
    characterItem->setCharacter(player);
    scene->addMovingObject(player, std::move(characterItem));

    for (const auto& bot : gameData.mapData->bots) {
        gameData.mapData->map->addBot(bot);
        auto botItem = std::make_unique<gui::BotGraphicsItem>();
        botItem->setCharacter(bot);
        scene->addMovingObject(bot, std::move(botItem));
    }

    gameData.game->setMap(gameData.mapData->map);
    gameData.view->setMap(gameData.mapData->map);
    gameData.game->setScene(scene);

    return true;
}

} // namespace bm
