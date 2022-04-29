#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "game/game.hpp"
#include "game/game_type.hpp"
#include "game/game_initialization_data.hpp"
#include "player_key_controls.hpp"
#include "game_dialogs.hpp"
//#include "game_dialogs_factory.hpp"

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

    void showMainMenu();

public slots:
    void startCampaignGame();
    void startSinglePlayerGame();
    void startNetworkGame();
    void connectToServer();
    void gameStatusChanged(bm::GameStatus newStatus);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private slots:
    void onGameCreationDialogFinished(int result);

private: // methods
    void showInitializationGameErrorsMessage(const QStringList& errors);
    void createNewGameInitializationData();
    void initializeGame(GameInitializationData& data);
    void startGame(const GameInitializationData& data);
    void createGameDialogs(GameType type, const std::shared_ptr<Player>& player);

private: // data
    Ui::MainWindow* ui_             = nullptr;
    MainMenuWidget* mainMenuWidget_ = nullptr;
    GameView*       gameView_       = nullptr;
    // TODO: delete old dialogs before assigning new.
    GameDialogs            gameDialogs_;
    PlayerKeyControls      keyControls_;
    GameInitializationData gameData_;
};

} // namespace gui
} // namespace bm

#endif // MAINWINDOW_HPP
