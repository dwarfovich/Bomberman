#include "game_view.hpp"

namespace bm {
namespace gui {
GameView::GameView(QWidget* parent) : QGraphicsView { parent }, scene_ { new GameScene { this } }
{
    setScene(scene_);
}

void GameView::setMap(const std::shared_ptr<bm::Map>& map)
{
    map_ = map;
    connect(map.get(), &Map::characterMoved, scene_, &GameScene::characterMoved);
    updateMap();
}

void GameView::updateMap()
{
    const int   cellSize = 50;
    const auto& cells    = map_->map();
    int         x        = 0;
    int         y        = 0;
    QBrush      concreteBrush { Qt::blue };

    for (size_t i = 0; i < cells.size(); ++i) {
        x                  = (i % map_->width()) * cellSize;
        y                  = (i / map_->width()) * cellSize;
        CellItem* cellItem = new CellItem { &cells[i] };
        cellItem->setPos(x, y);
        scene_->setCellItem(cellItem, i);

        //        if (cells[i].type == CellType::Empty) {
        //            scene_->addRect(x, y, cellSize, cellSize);
        //        } else {
        //            scene_->addRect(x, y, cellSize, cellSize, {}, concreteBrush);
        //        }
    }
    QBrush      playerBrush(Qt::green);
    const auto& player = map_->player();

    auto characterItem = std::make_unique<CharacterGraphicsItem>();
    characterItem->setCharacter(player);
    scene_->addCharacter(player, std::move(characterItem));
}

GameScene* GameView::scene() const
{
    return scene_;
}
} // namespace gui
} // namespace bm
