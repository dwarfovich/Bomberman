#include "create_player_dialog.hpp"
#include "ui_create_player_dialog.h"

namespace bm {
namespace gui {

CreatePlayerDialog::CreatePlayerDialog(QWidget *parent) : QDialog(parent), ui_(new Ui::CreatePlayerDialog)
{
    ui_->setupUi(this);

    connect(ui_->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui_->createButton, &QPushButton::clicked, this, &QDialog::accept);
}

CreatePlayerDialog::~CreatePlayerDialog()
{
    delete ui_;
}

QString CreatePlayerDialog::playerName() const
{
    return ui_->playerNameEdit->text();
}

} // namespace gui
} // namespace bm
