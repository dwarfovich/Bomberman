#ifndef BM_GUI_FAST_GAME_CREATION_DIALOG_HPP
#define BM_GUI_FAST_GAME_CREATION_DIALOG_HPP

#include "game_creation_dialog.hpp"

namespace bm {
class GameInitializationData;

namespace gui {

namespace Ui {
class FastGameCreationDialog;
}

class FastGameCreationDialog : public GameCreationDialog
{
    Q_OBJECT

public:
    explicit FastGameCreationDialog(QWidget *parent = nullptr);
    ~FastGameCreationDialog();

    const GameInitializationData &initializationData() const override;

private:
    std::shared_ptr<Map> chooseRandomMap() const;

private:
    Ui::FastGameCreationDialog *ui_;
};

} // namespace gui
} // namespace bm
#endif // BM_GUI_FAST_GAME_CREATION_DIALOG_HPP
