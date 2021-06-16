#include "game_scene.hpp"

namespace bm {
namespace gui {
    GameScene::GameScene(QObject* parent) : QGraphicsScene{parent}
    {
    }

    bool GameScene::setCellItem(CellItem&& item, size_t index)
    {
        try {
            if (index >= cellItems_.size()) {
                cellItems_.resize(index + 1);
            }
            cellItems_[index] = std::move(item);

            return (true);
        }
        catch (...) {
            return (false);
        }
    }
}  // namespace gui
}  // namespace bm
