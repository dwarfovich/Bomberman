#include "campaign_game_over_dialog.hpp"
#include "ui_campaign_game_over_dialog.h"
#include "game/game_result.hpp"
#include "game/player.hpp"

namespace bm {
namespace gui {

CampaignGameOverDialog::CampaignGameOverDialog(const std::shared_ptr<Player> &player, QWidget *parent)
    : GameOverDialog { player, parent }, ui_ { new Ui::CampaignGameOverDialog }
{
    ui_->setupUi(this);

    connect(ui_->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui_->continueButton, &QPushButton::clicked, this, &QDialog::accept);
}

CampaignGameOverDialog::~CampaignGameOverDialog()
{
    delete ui_;
}

void CampaignGameOverDialog::setGameResult(const GameResult &gameResult)
{
    if (gameResult.gameWon) {
        ui_->gameResultLabel->setText("Wow! You won!");
        ui_->continueButton->setText("Continue");
        player_->setCampaignLevel(player_->campaignLevel() + 1);
    } else {
        ui_->gameResultLabel->setText("Ooh! You lost!");
        ui_->continueButton->setText("Replay");
    }
}

} // namespace gui
} // namespace bm
