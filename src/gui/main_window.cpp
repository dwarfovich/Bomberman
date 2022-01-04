#include "main_window.hpp"
#include "ui_main_window.h"
#include "game/map_loader.hpp"
#include "game/game_initializer.hpp"
#include "game/game_factory.hpp"
#include "game_view.hpp"
#include "main_menu_widget.hpp"
#include "campaign_game_dialog.hpp"
#include "create_network_game_dialog.hpp"
#include "client_game_dialog.hpp"
#include "game_gui_initializer.hpp"
#include "game_over_dialog.hpp"
#include "net/client.hpp"

#include <QKeyEvent>
#include <QDir>
#include <QMessageBox>

//#include <iostream>

#include <QDebug>

namespace bm {
namespace gui {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow { parent }
    , ui_ { new ::Ui::MainWindow }
    , mainMenuWidget_ { new MainMenuWidget { this } }
    , gameView_ { new GameView { this } }
{
    ui_->setupUi(this);

    showMainMenu();

    connect(mainMenuWidget_, &MainMenuWidget::campaignGameRequest, this, &MainWindow::startCampaignGame);
    connect(mainMenuWidget_, &MainMenuWidget::newSinglePlayerGameRequest, this, &MainWindow::startSinglePlayerGame);
    connect(mainMenuWidget_, &MainMenuWidget::newNetworkGameRequest, this, &MainWindow::startNetworkGame);
    connect(mainMenuWidget_, &MainMenuWidget::connectToServerRequest, this, &MainWindow::connectToServer);
}

MainWindow::~MainWindow()
{
    // TODO: examine can you just deleteLater mainMenuWidget_.
    if (!mainMenuWidget_->parent()) {
        delete mainMenuWidget_;
    }
    delete ui_;
}

void MainWindow::showMainMenu()
{
    gameView_->hide();
    setCentralWidget(mainMenuWidget_);
    mainMenuWidget_->show();
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == keyControls_.moveUp) {
        gameData_.game->movePlayer(keyControls_.playerId, Direction::Upward);
    } else if (event->key() == keyControls_.moveRight) {
        gameData_.game->movePlayer(keyControls_.playerId, Direction::Right);
    } else if (event->key() == keyControls_.moveDown) {
        gameData_.game->movePlayer(keyControls_.playerId, Direction::Downward);
    } else if (event->key() == keyControls_.moveLeft) {
        gameData_.game->movePlayer(keyControls_.playerId, Direction::Left);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) {
        return;
    }

    if (event->key() == keyControls_.moveUp) {
        gameData_.game->stopPlayer(keyControls_.playerId);
    } else if (event->key() == keyControls_.moveRight) {
        gameData_.game->stopPlayer(keyControls_.playerId);
    } else if (event->key() == keyControls_.moveDown) {
        gameData_.game->stopPlayer(keyControls_.playerId);
    } else if (event->key() == keyControls_.moveLeft) {
        gameData_.game->stopPlayer(keyControls_.playerId);
    } else if (event->key() == keyControls_.placeBomb) {
        gameData_.game->placeBomb(keyControls_.playerId);
    }
}

void MainWindow::gameStatusChanged(GameStatus newStatus)
{
    if (newStatus == GameStatus::GameOver) {
        auto* gameOverDialog = gameDialogs_.gameOverDialog;
        gameOverDialog->setGameResult(gameData_.game->gameResult());
        auto gameOverDialogAnswer = gameOverDialog->exec();
        if (gameOverDialogAnswer == QDialog::Accepted) {
            gameDialogs_.creationDialog->reset();
            auto answer = gameDialogs_.creationDialog->exec();
            if (answer == QDialog::Accepted) {
                //        auto initializationData = createSinglePlayerGame(gameDialogs_.creationDialog->map());
                auto initializationData = gameDialogs_.creationDialog->initializationData();
                // TODO: Check if gameData has errors.
                initializeGame(initializationData);
                startGame(initializationData);
            } else {
                showMainMenu();
            }
        } else {
            showMainMenu();
        }
    }
}

void MainWindow::showInitializationGameErrorsMessage(const QStringList& errors)
{
    QString message = "Cann't initialize game\n";
    for (const auto& error : errors) {
        message += error + '\n';
    }
    QMessageBox::critical(this, "Error!", message);
}

void MainWindow::createNewGameInitializationData()
{
    gameData_             = {};
    gameData_.view        = gameView_;
    gameData_.scene       = new GameScene { gameView_ };
    gameData_.keyControls = &keyControls_;
}

void MainWindow::initializeGame(GameInitializationData& data)
{
    const auto& errors = game_ns::initializeGame(data);

    if (!errors.empty()) {
        showInitializationGameErrorsMessage(errors);
        return;
    }

    if (!data.scene) {
        data.scene                = new GameScene(gameView_);
        data.sceneConnectedToGame = false;
    }
    data.view        = gameView_;
    data.mainWindow  = this;
    data.keyControls = &keyControls_;

    initializeGameGui(data);
}

void MainWindow::startGame(const GameInitializationData& data)
{
    if (&gameData_ != &data) {
        gameData_ = data;
    }
    mainMenuWidget_->hide();
    mainMenuWidget_->setParent(nullptr);
    setCentralWidget(gameView_);
    gameView_->show();
    gameData_.game->start();
}

void MainWindow::startSinglePlayerGame()
{
    gameDialogs_ = createGameDialogs(this, GameType::Fast, mainMenuWidget_->selectedPlayer());

    auto answer = gameDialogs_.creationDialog->exec();
    if (answer == QDialog::Accepted) {
        //        auto initializationData = createSinglePlayerGame(gameDialogs_.creationDialog->map());
        auto initializationData = gameDialogs_.creationDialog->initializationData();
        // TODO: Check if gameData has errors.
        initializeGame(initializationData);
        startGame(initializationData);
    }
}

void MainWindow::startCampaignGame()
{
    const auto& player = mainMenuWidget_->selectedPlayer();
    if (player) {
        gameDialogs_ = createGameDialogs(this, GameType::Campaign, player);
        auto answer  = gameDialogs_.creationDialog->exec();
        if (answer == QDialog::Accepted) {
            //        auto initializationData = createSinglePlayerGame(gameDialogs_.creationDialog->map());
            auto initializationData = gameDialogs_.creationDialog->initializationData();
            // TODO: Check if gameData has errors.
            initializeGame(initializationData);
            startGame(initializationData);
        }
    } else {
        QMessageBox::information(this, "Cann't play campaign", "Please select correct player to play campaign");
    }
}

void MainWindow::startNetworkGame()
{
    // CreateNetworkGameDialog dialog;
    // auto                    answer = dialog.exec();
    const auto& player = mainMenuWidget_->selectedPlayer();
    gameDialogs_       = createGameDialogs(this, GameType::Server, player);
    auto answer        = gameDialogs_.creationDialog->exec();
    if (answer == QDialog::Accepted) {
        auto initializationData = gameDialogs_.creationDialog->initializationData();
        // TODO: Check if gameData has errors.
        initializeGame(initializationData);
        startGame(initializationData);
    }
}

void MainWindow::connectToServer()
{
    const auto& player = mainMenuWidget_->selectedPlayer();
    gameDialogs_       = createGameDialogs(this, GameType::Client, player);
    auto answer        = gameDialogs_.creationDialog->exec();
    if (answer == QDialog::Accepted) {
        auto initializationData = gameDialogs_.creationDialog->initializationData();
        // TODO: Check if gameData has errors.
        initializeGame(initializationData);
        startGame(initializationData);
    }

    //    ClientGameDialog dialog { mainMenuWidget_->selectedPlayer()->name() };
    //    auto             answer = dialog.exec();
    //    if (answer == QDialog::Accepted) {
    //        auto initializationData = dialog.initializationData();
    //        // TODO: Check if gameData has errors.
    //        initializeGame(initializationData);
    //        startGame(initializationData);
    //    }
}

} // namespace gui
} // namespace bm
