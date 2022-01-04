#ifndef BM_GUI_NETWORK_GAME_OVER_DIALOG_HPP
#define BM_GUI_NETWORK_GAME_OVER_DIALOG_HPP

#include "game_over_dialog.hpp"

namespace bm {
namespace gui {

namespace Ui {
class NetworkGameOverDialog;
}

class NetworkGameOverDialog : public GameOverDialog
{
    Q_OBJECT

public:
    explicit NetworkGameOverDialog(const std::shared_ptr<Player> &player, QWidget *parent = nullptr);
    ~NetworkGameOverDialog();

    void setGameResult(const GameResult &gameResult) override;

private:
    Ui::NetworkGameOverDialog *ui_;
};

} // namespace gui
} // namespace bm
#endif // BM_GUI_NETWORK_GAME_OVER_DIALOG_HPP
