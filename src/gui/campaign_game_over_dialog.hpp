#ifndef CAMPAIGN_GAME_OVER_DIALOG_HPP
#define CAMPAIGN_GAME_OVER_DIALOG_HPP

#include <QDialog>

namespace Ui {
class CampaignGameOverDialog;
}

class CampaignGameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CampaignGameOverDialog(QWidget *parent = nullptr);
    ~CampaignGameOverDialog();

private:
    Ui::CampaignGameOverDialog *ui_;
};

#endif // CAMPAIGN_GAME_OVER_DIALOG_HPP
