#include "game_over_dialog.hpp"
#include "ui_game_over_dialog.h"

namespace bm {
namespace gui {

GameOverDialog::GameOverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}

} // namespace gui
} // namespace bm
