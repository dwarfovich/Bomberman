#ifndef BM_GUI_FAST_GAME_OVER_DIALOG_HPP
#define BM_GUI_FAST_GAME_OVER_DIALOG_HPP

#include "game_over_dialog.hpp"

namespace bm {
namespace gui {

namespace Ui {
class FastGameOverDialog;
}

class FastGameOverDialog : public GameOverDialog
{
    Q_OBJECT

public:
    explicit FastGameOverDialog(QWidget *parent = nullptr);
    ~FastGameOverDialog();

private:
    Ui::FastGameOverDialog *ui_;
};

} // namespace gui
} // namespace bm
#endif // BM_GUI_FAST_GAME_OVER_DIALOG_HPP
