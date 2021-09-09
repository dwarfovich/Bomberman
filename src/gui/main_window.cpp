#include "main_window.hpp"
#include "ui_main_window.h"
#include "game/map_loader.hpp"
#include "game/game_initializer.hpp"
#include "game/game_factory.hpp"
#include "gui/game_view.hpp"
#include "gui/main_menu_widget.hpp"
#include "gui/create_network_game_dialog.hpp"
#include "gui/client_game_dialog.hpp"
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
        game_->movePlayer(keyControls_.playerId, Direction::Upward);
    } else if (event->key() == keyControls_.moveRight) {
        game_->movePlayer(keyControls_.playerId, Direction::Right);
    } else if (event->key() == keyControls_.moveDown) {
        game_->movePlayer(keyControls_.playerId, Direction::Downward);
    } else if (event->key() == keyControls_.moveLeft) {
        game_->movePlayer(keyControls_.playerId, Direction::Left);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) {
        return;
    }

    if (event->key() == keyControls_.moveUp) {
        game_->stopPlayer(keyControls_.playerId);
    } else if (event->key() == keyControls_.moveRight) {
        game_->stopPlayer(keyControls_.playerId);
    } else if (event->key() == keyControls_.moveDown) {
        game_->stopPlayer(keyControls_.playerId);
    } else if (event->key() == keyControls_.moveLeft) {
        game_->stopPlayer(keyControls_.playerId);
    } else if (event->key() == keyControls_.placeBomb) {
        game_->placeBomb(keyControls_.playerId);
    }
}

void MainWindow::initializeNetworkGame(const CreateNetworkGameDialog& dialog)
{
    const auto mapFile = QDir::currentPath() + "/maps/test_map.json";
    auto       mapData = map_loader::loadFromFile(mapFile);
    if (!mapData.map) {
        exit(1);
    }

    game_ = createNetworkGame(dialog.server(), mapData.map, mapData);

    if (!game_) {
        QMessageBox::critical(this, "Error", "Cannot create network game");
        return;
    }

    GameData gameData;
    gameData.mapData = &mapData;
    gameData.game    = game_.get();
    gameData.view    = gameView_;
    bool success     = true;
    if (success) {
        auto* scene = gameData.view->scene();

        QObject::connect(gameData.game, &Game::cellStructureChanged, scene, &gui::GameScene::onCellStructureChanged);
        QObject::connect(gameData.game, &Game::characterMoved, scene, &gui::GameScene::onCharacterMoved);
        QObject::connect(gameData.game, &Game::characterStartedMoving, scene, &gui::GameScene::onCharacterStartedMove);
        QObject::connect(gameData.game, &Game::characterStopped, scene, &gui::GameScene::onCharacterStopped);
        QObject::connect(gameData.game, &Game::bombPlaced, scene, &gui::GameScene::onBombPlaced);
        QObject::connect(gameData.game, &Game::bombExploded, scene, &gui::GameScene::onBombExploded);
        QObject::connect(gameData.game, &Game::explosionHappened, scene, &gui::GameScene::onExplosionHappened);
        QObject::connect(gameData.game, &Game::explosionFinished, scene, &gui::GameScene::onExplosionFinished);
        QObject::connect(gameData.game, &Game::objectDestroyed, scene, &gui::GameScene::onObjectDestroyed);

        for (uint8_t i = 0; i < 255; ++i) {
            auto bomberman = game_->bomberman(i);
            if (bomberman) {
                scene->addBomberman(bomberman);
            }
        }

        for (const auto& bot : gameData.mapData->bots) {
            scene->addBot(bot);
        }

        gameData.view->setMap(gameData.mapData->map);
        scene->setMap(gameData.mapData->map);

        keyControls_.playerId = game_->playerId();

        game_->start();
    } else {
        exit(1);
    }
}

void MainWindow::initializeClientGame(const ClientGameDialog& dialog)
{
    //    const auto mapFile = QDir::currentPath() + "/maps/test_map.json";
    //    auto       mapData = map_loader::loadFromFile(mapFile);
    //    if (!mapData.map) {
    //        exit(1);
    //    }

    game_ = createClientGame(dialog.client());

    if (!game_) {
        QMessageBox::critical(this, "Error", "Cannot create client game");
        return;
    }

    //    GameData gameData;
    //    gameData.mapData = &mapData;
    //    gameData.game    = game_.get();
    //    gameData.view    = gameView_;
    // bool success = initializeGame(data);
    bool success = true;
    if (success) {
        // TODO: Move game initialization into it's own function.
        // TODO: And refactor it.
        auto* scene = gameView_->scene();

        //        QObject::connect(
        //            dialog.client()->initializedMap().get(), &Map::cellChanged, scene, &gui::GameScene::cellChanged);
        //        QObject::connect(
        //            dialog.client()->initializedMap().get(), &Map::objectMoved, scene,
        //            &gui::GameScene::onCharacterMoved);
        QObject::connect(game_.get(), &Game::cellStructureChanged, scene, &gui::GameScene::onCellStructureChanged);
        QObject::connect(game_.get(), &Game::characterMoved, scene, &gui::GameScene::onCharacterMoved);
        QObject::connect(game_.get(), &Game::characterStartedMoving, scene, &gui::GameScene::onCharacterStartedMove);
        QObject::connect(game_.get(), &Game::characterStopped, scene, &gui::GameScene::onCharacterStopped);
        QObject::connect(game_.get(), &Game::bombPlaced, scene, &gui::GameScene::onBombPlaced);
        QObject::connect(game_.get(), &Game::bombExploded, scene, &gui::GameScene::onBombExploded);
        QObject::connect(game_.get(), &Game::explosionHappened, scene, &gui::GameScene::onExplosionHappened);
        QObject::connect(game_.get(), &Game::explosionFinished, scene, &gui::GameScene::onExplosionFinished);
        QObject::connect(game_.get(), &Game::objectDestroyed, scene, &gui::GameScene::onObjectDestroyed);

        // TODO: Refactor - get bombermans count.
        for (uint8_t i = 0; i < 255; ++i) {
            auto bomberman = game_->bomberman(i);
            if (bomberman) {
                scene->addBomberman(bomberman);
            }
        }

        auto bots = dialog.client()->initializedMap()->bots();
        for (const auto& bot : dialog.client()->initializedMap()->bots()) {
            scene->addBot(bot);
        }

        scene->setMap(dialog.client()->initializedMap());
        gameView_->setMap(dialog.client()->initializedMap());
    } else {
        exit(1);
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

void MainWindow::startSinglePlayerGame()
{
    const auto mapFile = QDir::currentPath() + "/maps/test_map.json";
    auto       mapData = map_loader::loadFromFile(mapFile);
    if (!mapData.map) {
        QMessageBox::critical(this, "Error!", "Cann't load map");
        exit(1);
    }

    auto gameData      = createSinglePlayerGame(mapData.map);
    gameData.scene     = new GameScene(gameView_);
    gameData.view      = gameView_;
    const auto& errors = initializeGame(gameData);

    if (!errors.empty()) {
        showInitializationGameErrorsMessage(errors);
        return;
    }

    game_                 = gameData.game;
    keyControls_.playerId = game_->getPlayerBomberman();
    mainMenuWidget_->hide();
    setCentralWidget(gameView_);
    gameView_->show();
    game_->start();
}

void MainWindow::startNetworkGame()
{
    CreateNetworkGameDialog dialog;
    auto                    answer = dialog.exec();
    if (answer == QDialog::Accepted) {
        auto initializationData = dialog.initializationData();

        initializationData.scene = new GameScene(gameView_);
        initializationData.view  = gameView_;
        const auto& errors       = initializeGame(initializationData);

        if (!errors.empty()) {
            showInitializationGameErrorsMessage(errors);
            return;
        }

        keyControls_.playerId = initializationData.playerBomberman;
        game_                 = initializationData.game;
        if (game_) {
            mainMenuWidget_->hide();
            setCentralWidget(gameView_);
            gameView_->show();
            game_->start();
        }
    }
}

void MainWindow::connectToServer()
{
    ClientGameDialog dialog;
    auto             answer = dialog.exec();
    if (answer == QDialog::Accepted) {
        initializeClientGame(dialog);
        mainMenuWidget_->hide();
        setCentralWidget(gameView_);
        gameView_->show();
        game_->start();
    }
}

} // namespace gui
} // namespace bm
