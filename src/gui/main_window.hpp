#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "game/game.hpp"

#include <QMainWindow>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace bm {
namespace gui {
class GameView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow*       ui_       = nullptr;
    GameView*             gameView_ = nullptr;
    std::unique_ptr<Game> game_;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};

} // namespace gui
} // namespace bm

#endif // MAINWINDOW_HPP
