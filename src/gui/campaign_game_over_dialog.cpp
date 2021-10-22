#include "campaign_game_over_dialog.hpp"
#include "ui_campaign_game_over_dialog.h"

CampaignGameOverDialog::CampaignGameOverDialog(QWidget *parent) : QDialog(parent), ui_(new Ui::CampaignGameOverDialog)
{
    ui_->setupUi(this);
    connect(ui_->cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui_->continueButton, &QPushButton::clicked, this, &QDialog::accept);
}

CampaignGameOverDialog::~CampaignGameOverDialog()
{
    delete ui_;
}
