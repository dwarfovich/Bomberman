#ifndef BM_GUI_CREATE_PLAYER_DIALOG_HPP
#define BM_GUI_CREATE_PLAYER_DIALOG_HPP

#include <QDialog>

namespace bm {
namespace gui {
namespace Ui {
class CreatePlayerDialog;
}

class CreatePlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePlayerDialog(QWidget *parent = nullptr);
    ~CreatePlayerDialog();

    QString playerName() const;

private:
    Ui::CreatePlayerDialog *ui_;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_CREATE_PLAYER_DIALOG_HPP
