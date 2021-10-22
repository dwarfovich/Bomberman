#include "fast_game_over_dialog.hpp"
#include "ui_fast_game_over_dialog.h"
#include "game/game_result.hpp"

namespace bm {
namespace gui {

FastGameOverDialog::FastGameOverDialog(QWidget *parent) : GameOverDialog { parent }, ui_ { new Ui::FastGameOverDialog }
{
    ui_->setupUi(this);
    connect(ui_->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui_->onceMoreGameButton, &QPushButton::clicked, this, &QDialog::accept);
}

FastGameOverDialog::~FastGameOverDialog()
{
    delete ui_;
}

void FastGameOverDialog::setGameResult(const GameResult &gameResult)
{
    if (gameResult.gameWon) {
        ui_->gameResultLabel->setText("Congratulations! You won!");
    } else {
        ui_->gameResultLabel->setText("Oh! You loose!");
    }

    QString botsKilledMessage = "You killed " + QString::number(gameResult.characterIdsLoose.size()) + ' ';
    if (gameResult.characterIdsLoose.size() == 1) {
        botsKilledMessage += "bot.";
    } else {
        botsKilledMessage += "bots.";
    }
    ui_->botsKilledLabel->setText(botsKilledMessage);
}

} // namespace gui
} // namespace bm
