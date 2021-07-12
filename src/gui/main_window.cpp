#include "main_window.hpp"
#include "ui_main_window.h"
#include "gui/game_view.hpp"
#include "game/map_loader.hpp"

#include <QKeyEvent>

#include <iostream>

#include <QDebug>

namespace bm {
namespace gui {
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow { parent }, ui_ { new Ui::MainWindow }, gameView_ { new GameView { this } }
{
    ui_->setupUi(this);

    std::shared_ptr<Map> map    = createTestMap();
    auto                 player = std::make_shared<Bomberman>();
    // 44
    player->moveData.location = map->cellIndexToCenterLocation(44);
    map->setPlayer(player);
    game_.setMap(map);
    game_.setScene(gameView_->scene());
    gameView_->setMap(map);
    setCentralWidget(gameView_);
    game_.start();
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
