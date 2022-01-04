#include "network_game_over_dialog.hpp"
#include "ui_network_game_over_dialog.h"
#include "game/game_result.hpp"
#include "game/player.hpp"

namespace bm {
namespace gui {

NetworkGameOverDialog::NetworkGameOverDialog(const std::shared_ptr<Player> &player, QWidget *parent)
    : GameOverDialog { player, parent }, ui_ { new Ui::NetworkGameOverDialog }
{
    ui_->setupUi(this);

    connect(ui_->exitButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui_->playAgainButton, &QPushButton::clicked, this, &QDialog::accept);
}

NetworkGameOverDialog::~NetworkGameOverDialog()
{
    delete ui_;
}

void NetworkGameOverDialog::setGameResult(const GameResult &gameResult)
{
    QString additionalInfo;
    if (gameResult.characterIdWon == player_->currentGameBombermanId()) {
        ui_->gameReultLabel->setText("Yeah! You won!");
        additionalInfo = "You defeated: ";

    } else {
        if (gameResult.gameWon) {
            ui_->gameReultLabel->setText("Oh no, " + player_->name() + "! You lose!");
        } else {
            ui_->gameReultLabel->setText("Oh, noone wins!");
        }
        additionalInfo = "Other losers are: ";
    }
    if (gameResult.characterIdsLoose.size() > 0) {
        for (size_t i = 0; i < gameResult.losePlayers.size(); ++i) {
            // TODO: fix showing current player's name in additional info.
            additionalInfo += gameResult.losePlayers[i];
            if (i + 1 == gameResult.losePlayers.size()) {
                additionalInfo += '!';
            } else {
                additionalInfo += ", ";
            }
        }
        ui_->addinitionalInfoLabel->setText(additionalInfo);
    } else {
        ui_->addinitionalInfoLabel->clear();
    }
}

} // namespace gui
} // namespace bm
