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
}

GameScene* GameView::scene() const
{
    return scene_;
}
} // namespace gui
} // namespace bm
