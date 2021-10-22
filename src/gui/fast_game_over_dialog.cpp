#include "fast_game_over_dialog.hpp"
#include "ui_fast_game_over_dialog.h"

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

} // namespace gui
} // namespace bm
