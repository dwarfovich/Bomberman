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
    explicit FastGameOverDialog(const std::shared_ptr<Player> &player, QWidget *parent = nullptr);
    ~FastGameOverDialog();

    void setGameResult(const GameResult &gameResult) override;

private:
    Ui::FastGameOverDialog *ui_;
};

} // namespace gui
} // namespace bm
#endif // BM_GUI_FAST_GAME_OVER_DIALOG_HPP
