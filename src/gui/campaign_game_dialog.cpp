#include "campaign_game_dialog.hpp"
#include "ui_campaign_game_dialog.h"
#include "game/server_game.hpp"

namespace bm {
namespace gui {

CampaignGameDialog::CampaignGameDialog(const std::shared_ptr<Player> player, QWidget *parent)
    : GameCreationDialog { parent }
    , ui_ { new Ui::CampaignGameDialog }
    , player_ { player }
    , game_ { std::make_shared<ServerGame>() }
{
    ui_->setupUi(this);
}

CampaignGameDialog::~CampaignGameDialog()
{
    delete ui_;
}

const GameInitializationData &CampaignGameDialog::initializationData() const
{
    initializationData_.game            = game_;
    initializationData_.map             = game_->map();
    initializationData_.playerBomberman = game_->playerId();

    return initializationData_;
}

} // namespace gui
} // namespace bm
