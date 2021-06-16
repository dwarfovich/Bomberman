#include "game_view.hpp"

namespace bm {
namespace gui {
    GameView::GameView(QWidget* parent) : QGraphicsView{parent}, scene_{new GameScene{this}}
    {
        setScene(scene_);
    }

    void GameView::setMap(const std::shared_ptr<bm::Map>& map)
    {
        map_ = map;
        updateMap();
    }

    void GameView::updateMap()
    {
        const int cellSize = 50;
        const auto& cells = map_->map();
        int x = 0;
        int y = 0;
        QBrush concreteBrush{Qt::blue};

        for (size_t i = 0; i < cells.size(); ++i) {
            x = (i % map_->width()) * cellSize;
            y = (i / map_->width()) * cellSize;
            if (cells[i].type == CellType::Empty) {
                scene_->addRect(x, y, cellSize, cellSize);
            }
            else {
                scene_->addRect(x, y, cellSize, cellSize, {}, concreteBrush);
            }
        }

        QBrush playerBrush(Qt::green);
        const auto& player = map_->player();

        auto location = player->location;

        location.setX(location.x() * cellSize);
        location.setY(location.y() * cellSize);
        scene_->addEllipse(location.x(), location.y(), cellSize, cellSize, {}, playerBrush);
    }
}  // namespace gui
}  // namespace bm
