#include "game_over_dialog.hpp"
#include "ui_game_over_dialog.h"

namespace bm {
namespace gui {

GameOverDialog::GameOverDialog(QWidget *parent) : QDialog(parent), ui_(new Ui::GameOverDialog)
{
    ui_->setupUi(this);
}

GameOverDialog::~GameOverDialog()
{
    delete ui_;
}

void GameOverDialog::setGameResult(const GameResult &gameResult)
{}

} // namespace gui
} // namespace bm
