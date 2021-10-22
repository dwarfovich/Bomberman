#include "fast_game_creation_dialog.hpp"
#include "ui_fast_game_creation_dialog.h"
#include "game/single_player_game_process.hpp"
#include "game/server_game.hpp"
#include "game/game_initialization_data.hpp"
#include "game/map_loader.hpp"

#include <QFile>
#include <QDir>
#include <QRandomGenerator>

namespace bm {
namespace gui {

FastGameCreationDialog::FastGameCreationDialog(QWidget* parent, const std::shared_ptr<Player>& player)
    : GameCreationDialog { parent, player }, ui_ { new Ui::FastGameCreationDialog }
{
    ui_->setupUi(this);

    connect(ui_->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui_->startButton, &QPushButton::clicked, this, &QDialog::accept);
}

FastGameCreationDialog::~FastGameCreationDialog()
{
    delete ui_;
}

const GameInitializationData& FastGameCreationDialog::initializationData() const
{
    static GameInitializationData data;
    data.game            = std::make_shared<ServerGame>();
    const auto& map      = chooseRandomMap();
    auto        respawns = map->respawnPlaces(RespawnType::Bomberman);
    if (respawns.size() > 0) {
        auto bomberman = std::make_shared<Bomberman>();
        bomberman->setCoordinates(map->indexToCellCenterCoordinates(respawns[0]));
        map->addBomberman(bomberman);
        data.playerBomberman = bomberman->id();
    }
    data.game->setMap(map);
    auto gameProcess = std::make_unique<SinglePlayerGameProcess>();
    gameProcess->setGame(data.game);
    data.game->setGameProcessHandler(std::move(gameProcess));
    data.map = data.game->map();

    return data;
}

std::shared_ptr<Map> FastGameCreationDialog::chooseRandomMap() const
{
    const auto& mapsFolder = QDir { QDir::currentPath() + "/maps/" };
    auto        maps       = mapsFolder.entryList({ "*.json" });
    if (maps.size() > 0) {
        auto index = QRandomGenerator::system()->bounded(maps.size());
        // TODO: change map index to rnadom 'index'.
        const auto& mapFile = mapsFolder.filePath(maps[1]);
        return map_loader::loadFromFile(mapFile).map;
    } else {
        return nullptr;
    }
}

} // namespace gui
} // namespace bm
