#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "cell_item.hpp"
#include "character_graphics_item.hpp"

#include <QGraphicsScene>

#include <vector>
#include <unordered_map>

namespace bm {
class Character;

namespace gui {
class CellItem;

class GameScene : public QGraphicsScene
{
public:
    explicit GameScene(QObject* parent = nullptr);

    bool setCellItem(CellItem* item, size_t index);
    void addCharacter(const std::shared_ptr<MovingObject>& character, std::unique_ptr<CharacterGraphicsItem>);

public slots:
    void characterMoved(const std::shared_ptr<MovingObject>& character);
    void cellChanged(size_t index);

private:
    QPoint mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const;

private:
    using CharactersItems = std::unordered_map<std::shared_ptr<MovingObject>, std::unique_ptr<CharacterGraphicsItem>>;
    CharactersItems        characters_;
    std::vector<CellItem*> cellItems_;
    const int              cellSize_;
};

} // namespace gui
} // namespace bm

#endif // GAMESCENE_HPP
