#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "game/game.hpp"
#include "player_key_controls.hpp"

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
class MainMenuWidget;
class CreateNetworkGameDialog;
class ClientGameDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

public slots:
    void startSinglePlayerGame();
    void startNetworkGame();
    void connectToServer();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private: // methods
    void initializeNetworkGame(const CreateNetworkGameDialog& dialog);
    void initializeClientGame(const ClientGameDialog& dialog);
    void showInitializationGameErrorsMessage(const QStringList& errors);

private: // data
    Ui::MainWindow*       ui_             = nullptr;
    MainMenuWidget*       mainMenuWidget_ = nullptr;
    PlayerKeyControls     keyControls_;
    GameView*             gameView_ = nullptr;
    std::shared_ptr<Game> game_;
};

} // namespace gui
} // namespace bm

#endif // MAINWINDOW_HPP
