#include "main_window.hpp"
#include "ui_main_window.h"
#include "game/map_loader.hpp"
#include "game/game_initializer.hpp"
#include "game/game_factory.hpp"
#include "game_view.hpp"
#include "main_menu_widget.hpp"
#include "create_network_game_dialog.hpp"
#include "client_game_dialog.hpp"
#include "game_gui_initializer.hpp"
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

    gameView_->hide();

    setCentralWidget(mainMenuWidget_);

    connect(mainMenuWidget_, &MainMenuWidget::newSinglePlayerGameRequest, this, &MainWindow::startSinglePlayerGame);
    connect(mainMenuWidget_, &MainMenuWidget::newNetworkGameRequest, this, &MainWindow::startNetworkGame);
    connect(mainMenuWidget_, &MainMenuWidget::connectToServerRequest, this, &MainWindow::connectToServer);
}

MainWindow::~MainWindow()
{
    delete ui_;
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

    data.scene       = new GameScene(gameView_);
    data.view        = gameView_;
    data.keyControls = &keyControls_;
    initializaGameGui(data);
}

void MainWindow::startGame(const GameInitializationData& data)
{
    gameData_ = data;
    mainMenuWidget_->hide();
    setCentralWidget(gameView_);
    gameView_->show();
    gameData_.game->start();
}

void MainWindow::startSinglePlayerGame()
{
    const auto mapFile = QDir::currentPath() + "/maps/test_map.json";
    auto       mapData = map_loader::loadFromFile(mapFile);
    if (!mapData.map) {
        QMessageBox::critical(this, "Error!", "Cann't load map");
        exit(1);
    }

    auto initializationData = createSinglePlayerGame(mapData.map);
    // TODO: Check if gameData has errors.
    initializeGame(initializationData);
    startGame(initializationData);
}

void MainWindow::startNetworkGame()
{
    CreateNetworkGameDialog dialog;
    auto                    answer = dialog.exec();
    if (answer == QDialog::Accepted) {
        auto initializationData = dialog.initializationData();
        // TODO: Check if gameData has errors.
        initializeGame(initializationData);
        startGame(initializationData);
    }
}

void MainWindow::connectToServer()
{
    ClientGameDialog dialog;
    auto             answer = dialog.exec();
    if (answer == QDialog::Accepted) {
        auto initializationData = dialog.initializationData();
        // TODO: Check if gameData has errors.
        initializeGame(initializationData);
        startGame(initializationData);
    }
}

} // namespace gui
} // namespace bm
