#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "game/game.hpp"
#include "player_key_controls.hpp"
#include "game/game_initialization_data.hpp"

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
    void startCampaignGame();
    void startSinglePlayerGame();
    void startNetworkGame();
    void connectToServer();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private: // methods
    void showInitializationGameErrorsMessage(const QStringList& errors);
    void createNewGameInitializationData();
    void initializeGame(GameInitializationData& data);
    void startGame(const GameInitializationData& data);

private: // data
    Ui::MainWindow*        ui_             = nullptr;
    MainMenuWidget*        mainMenuWidget_ = nullptr;
    PlayerKeyControls      keyControls_;
    GameView*              gameView_ = nullptr;
    GameInitializationData gameData_;
};

} // namespace gui
} // namespace bm

#endif // MAINWINDOW_HPP
