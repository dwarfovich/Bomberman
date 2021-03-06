#include "campaign_game_dialog.hpp"
#include "ui_campaign_game_dialog.h"
#include "game/player.hpp"
#include "game/server_game.hpp"
#include "game/player.hpp"
#include "game/campaign.hpp"
#include "game/map_loader.hpp"
#include "game/single_player_game_process.hpp"

#include <QDir>

namespace bm {
namespace gui {

CampaignGameDialog::CampaignGameDialog(const std::shared_ptr<Player> &player, QWidget *parent)
    : GameCreationDialog { parent, player }
    , ui_ { new Ui::CampaignGameDialog }
    , game_ { std::make_shared<ServerGame>() }
    , player_ { player }
{
    ui_->setupUi(this);

    connect(ui_->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui_->startButton, &QPushButton::clicked, this, &QDialog::accept);

    greetPlayer(player_->name());
    setCurrentLevel(player_->campaignLevel());
}

CampaignGameDialog::~CampaignGameDialog()
{
    delete ui_;
}

const GameInitializationData &CampaignGameDialog::initializationData() const
{
    // TODO: Make loading map uniform, move default map's dir into MapLoader.
    const QDir mapFolder = QDir::currentPath() + "/maps/";
    // TODO: Make campaign level of type size_t everywhere.
    auto     level = player_->campaignLevel();
    Campaign campaign;
    auto     mapFile = campaign.mapForCampaignLevel(level);
    if (mapFile.isEmpty()) {
        static GameInitializationData empty;
        empty.errors.append("No map file for level " + QString::number(level));
        return empty;
    }

    const auto &mapPath = mapFolder.filePath(mapFile);
    const auto &map     = map_loader::loadFromFile(mapPath).map;

    // TODO: Concider move static const empty entities somewhere.
    if (!map) {
        static GameInitializationData empty;
        empty.errors.append("Cannot load map from file " + mapPath);
        return empty;
    }

    auto respawns = map->respawnPlaces(RespawnType::Bomberman);
    if (respawns.size() > 0) {
        auto bomberman = std::make_shared<Bomberman>();
        bomberman->setCoordinates(map->indexToCellCenterCoordinates(respawns[0]));
        map->addBomberman(bomberman);
        initializationData_.playerBomberman = bomberman->id();
    } else {
        static GameInitializationData empty;
        empty.errors.append("Map " + map->name() + " has no respawn places for bomberman");
    }

    game_->setMap(map);
    initializationData_.game = game_;
    initializationData_.map  = game_->map();
    // TODO: Set game process somewhere, may be in game factory.
    auto gameProcess = std::make_unique<SinglePlayerGameProcess>();
    gameProcess->setGame(initializationData_.game);
    initializationData_.game->setGameProcessHandler(std::move(gameProcess));

    return initializationData_;
}

void CampaignGameDialog::greetPlayer(const QString &playerName)
{
    ui_->greetingsLabel->setText("Hello, " + playerName + '!');
}

void CampaignGameDialog::setCurrentLevel(size_t currentLevel)
{
    ui_->currentLevelLabel->setText("You're on level " + QString::number(currentLevel + 1));
}

} // namespace gui
} // namespace bm

const std::shared_ptr<bm::Map> &bm::gui::CampaignGameDialog::map() const
{
    if (game_) {
        return game_->map();
    } else {
        static const std::shared_ptr<bm::Map> empty { nullptr };
        return empty;
    }
}

void bm::gui::CampaignGameDialog::reset()
{
    greetPlayer(player_->name());
    setCurrentLevel(player_->campaignLevel());
}
