#include "game_initializer.hpp"
#include "game_initialization_data.hpp"
#include "map_loader.hpp"
#include "game.hpp"
#include "bot_factory.hpp"
#include "gui/game_scene.hpp"
#include "gui/game_view.hpp"

#include <QObject>

namespace bm {
namespace game_ns {

QStringList initializeGame(const GameInitializationData& data)
{
    Q_ASSERT(data.game);
    Q_ASSERT(data.map);
    Q_ASSERT(data.playerBomberman != invalidObjectId);

    QStringList errors;

    details::initializeBots(data, errors);
    details::initializeBombermans(data, errors);

    if (!errors.empty()) {
        return errors;
    }

    data.game->setPlayerBomberman(data.playerBomberman);

    data.game->setMap(data.map);

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

} // namespace game_ns
} // namespace bm
