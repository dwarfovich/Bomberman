#include "campaign_game_dialog.hpp"
#include "ui_campaign_game_dialog.h"
#include "game/server_game.hpp"

namespace bm {
namespace gui {

CampaignGameDialog::CampaignGameDialog(const std::shared_ptr<Player> &player, QWidget *parent)
    : GameCreationDialog { parent, player }
    , ui_ { new Ui::CampaignGameDialog }
    , game_ { std::make_shared<ServerGame>() }
{
    ui_->setupUi(this);

    connect(ui_->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui_->startButton, &QPushButton::clicked, this, &QDialog::accept);
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

const std::shared_ptr<bm::Map> &bm::gui::CampaignGameDialog::map() const
{
    if (game_) {
        return game_->map();
    } else {
        static const std::shared_ptr<bm::Map> empty { nullptr };
        return empty;
    }
}
