#ifndef BM_GUI_GAME_OVER_DIALOG_HPP
#define BM_GUI_GAME_OVER_DIALOG_HPP

#include <QDialog>

namespace bm {
class GameResult;

namespace gui {

namespace Ui {
class GameOverDialog;
}

class GameOverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GameOverDialog(QWidget *parent = nullptr);
    ~GameOverDialog();

    virtual void setGameResult(const GameResult &gameResult);

private:
    Ui::GameOverDialog *ui_;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_GAME_OVER_DIALOG_HPP
