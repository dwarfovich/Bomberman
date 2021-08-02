#include "main_window.hpp"
#include "ui_main_window.h"
#include "game/map_loader.hpp"
#include "game/game_initializer.hpp"
#include "gui/game_view.hpp"

#include <QKeyEvent>
#include <QDir>

#include <iostream>

#include <QDebug>

namespace bm {
namespace gui {
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow { parent }, ui_ { new Ui::MainWindow }, gameView_ { new GameView { this } }
{
    ui_->setupUi(this);

    // std::shared_ptr<Map> map = map_loader::createTestMap();

    // game_.setScene(gameView_->scene());
    // game_.setMap(mapData.map);

    // auto player = std::make_shared<Bomberman>();
    // 44
    // player->movementData().coordinates = map->indexToCellCenterCoordinates(44);
    // player->setCoordinates(mapData.map->indexToCellCenterCoordinates(44));
    //    map->setPlayer(player);
    // game_.setPlayer(player);

    // game_.setMap(map);
    // game_.setScene(gameView_->scene());
    // gameView_->setMap(mapData.map);
    setCentralWidget(gameView_);

    const auto mapFile = QDir::currentPath() + "/maps/test_map.json";
    auto       mapData = map_loader::loadFromFile(mapFile);
    if (!mapData.map) {
        exit(1);
    }

    GameData data;
    data.mapData = &mapData;
    data.game    = &game_;
    data.view    = gameView_;
    bool success = initializeGame(data);
    if (success) {
        game_.start();
    } else {
        exit(1);
    }
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W) {
        game_.movePlayer(Direction::Upward);
    } else if (event->key() == Qt::Key_D) {
        game_.movePlayer(Direction::Right);
    } else if (event->key() == Qt::Key_S) {
        game_.movePlayer(Direction::Downward);
    } else if (event->key() == Qt::Key_A) {
        game_.movePlayer(Direction::Left);
    }

    std::cout << "Moving" << std::endl;
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if (event->isAutoRepeat()) {
        return;
    }
    if (event->key() == Qt::Key_W) {
        game_.stopPlayer(Direction::Upward);
    } else if (event->key() == Qt::Key_D) {
        game_.stopPlayer(Direction::Right);
    } else if (event->key() == Qt::Key_S) {
        game_.stopPlayer(Direction::Downward);
    } else if (event->key() == Qt::Key_A) {
        game_.stopPlayer(Direction::Left);
    } else if (event->key() == Qt::Key_Space) {
        game_.placeBomb();
    }
}

} // namespace gui
} // namespace bm
