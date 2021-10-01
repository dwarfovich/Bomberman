#ifndef BM_GUI_GAMEDIALOGS_HPP
#define BM_GUI_GAMEDIALOGS_HPP

#include <Qt>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

namespace bm {
namespace gui {
class GameCreationDialog;
class GameOverDialog;

class GameDialogs
{
public:
    explicit GameDialogs(QWidget* parentWidget = nullptr);

private:
    QWidget*            parentWidget_;
    GameCreationDialog* creationDialog_;
    GameOverDialog*     gameOverDialog_;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_GAMEDIALOGS_HPP
