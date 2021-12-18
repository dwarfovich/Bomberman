#include "game_over_dialog.hpp"
#include "ui_game_over_dialog.h"

namespace bm {
namespace gui {

GameOverDialog::GameOverDialog(const std::shared_ptr<Player> &player, QWidget *parent)
    : QDialog { parent }, player_ { player }, ui_ { new Ui::GameOverDialog }
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
