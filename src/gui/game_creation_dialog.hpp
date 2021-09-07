#ifndef BM_GUI_GAMECREATIONDIALOG_HPP
#define BM_GUI_GAMECREATIONDIALOG_HPP

#include <QDialog>

namespace bm {
class GameInitializationData;

namespace gui {

class GameCreationDialog : public QDialog
{
public:
    explicit GameCreationDialog(QWidget* parent = nullptr);

    virtual const GameInitializationData& initializationData() const = 0;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_GAMECREATIONDIALOG_HPP
