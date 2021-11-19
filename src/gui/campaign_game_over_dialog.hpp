#ifndef BM_GUI_CAMPAIGN_GAME_OVER_DIALOG_HPP
#define BM_GUI_CAMPAIGN_GAME_OVER_DIALOG_HPP

#include "game_over_dialog.hpp"

namespace bm {
namespace gui {

namespace Ui {
class CampaignGameOverDialog;
}

class CampaignGameOverDialog : public GameOverDialog
{
    Q_OBJECT

public:
    explicit CampaignGameOverDialog(QWidget *parent = nullptr);
    ~CampaignGameOverDialog();

private:
    Ui::CampaignGameOverDialog *ui_;
};

} // namespace gui
} // namespace bm
#endif // BM_GUI_CAMPAIGN_GAME_OVER_DIALOG_HPP
