#include "main_window.hpp"
#include "ui_main_window.h"
#include "gui/game_view.hpp"
#include "game/map_loader.hpp"

#include <QKeyEvent>

namespace bm {
namespace gui {
    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow{parent}
        , ui_{new Ui::MainWindow}
        , gameView_{new GameView{this}}
    {
        ui_->setupUi(this);

        std::shared_ptr<Map> map = createTestMap();
        auto player = std::make_shared<Bomberman>();

        player->location = {5, 5};
        map->setPlayer(player);
        game_.setMap(map);
        gameView_->setMap(map);
        setCentralWidget(gameView_);
    }

    MainWindow::~MainWindow()
    {
        delete ui_;
    }

    void MainWindow::keyPressEvent(QKeyEvent* event)
    {
        if (event->key() == Qt::Key_W) {
            game_.movePlayer(Direction::Upward);
        }
    }
}  // namespace gui
}  // namespace bm
