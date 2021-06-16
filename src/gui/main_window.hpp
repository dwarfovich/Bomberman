#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "game/game_loop.hpp"

#include <QMainWindow>

#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace bm {
namespace gui {
    class GameView;
}
}  // namespace bm

namespace bm {
namespace gui {
    class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow* ui_ = nullptr;
        GameView* gameView_ = nullptr;
        GameLoop game_;

        // QWidget interface
    protected:
        void keyPressEvent(QKeyEvent* event) override;
    };
}  // namespace gui
}  // namespace bm
#endif // MAINWINDOW_HPP
