#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "cell_item.hpp"
#include <QGraphicsScene>
#include <vector>
#include <unordered_set>

namespace bm {
struct Character;

namespace gui {
    class CellItem;

    class GameScene : public QGraphicsScene {
    public:
        explicit GameScene(QObject* parent = nullptr);

        bool setCellItem(CellItem&& item, size_t index);

    private:
        std::unordered_set<std::shared_ptr<Character> > characters_;
        std::vector<CellItem> cellItems_;
    };
}  // namespace gui
}  // namespace bm

#endif // GAMESCENE_HPP
