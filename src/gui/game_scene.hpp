#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "sprite_factory.hpp"
#include "cell_item.hpp"
#include "character_graphics_item.hpp"

#include <QGraphicsScene>

#include <vector>
#include <unordered_map>

namespace bm {
class Bomberman;
class Character;
class Map;

namespace gui {
class CellItem;
class SpriteGraphicsObject;

class GameScene : public QGraphicsScene
{
public:
    explicit GameScene(QObject* parent = nullptr);

    void setMap(const std::shared_ptr<Map>& map);
    void addBomberman(const std::shared_ptr<Bomberman>& bomberman);

    void addCellItem(std::unique_ptr<SpriteGraphicsObject> item);
    void addCharacterItem(std::unique_ptr<SpriteGraphicsObject> item);

    bool setCellItem(CellItem* item, size_t index);
    void addMovingObject(const std::shared_ptr<MovingObject>& object, std::unique_ptr<CharacterGraphicsItem> item);
    void destroyItemForObject(const std::shared_ptr<MovingObject>& object);
    void removeAllObjects();

public slots:
    void onCharacterMoved(const std::shared_ptr<MovingObject>& character);
    void cellChanged(size_t index);

private:
    QPoint mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const;

private:
    std::vector<SpriteGraphicsObject*> cellItems_;
    using CharacterMap = std::unordered_map<std::shared_ptr<Character>, SpriteGraphicsObject*>;
    CharacterMap        characterMap_;
    SpriteObjectFactory spriteFactory_;

    using MovingItems = std::unordered_map<std::shared_ptr<MovingObject>, std::unique_ptr<CharacterGraphicsItem>>;
    MovingItems movingObjects_;
    //    std::vector<CellItem*> cellItems_;

    const int cellSize_;
    //    size_t widthInCells_ = 0;
    //    size_t heightInCells_ = 0;
};

} // namespace gui
} // namespace bm

#endif // GAMESCENE_HPP
