#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "sprite_factory.hpp"
#include "cell_item.hpp"
#include "character_graphics_item.hpp"

#include <QGraphicsScene>
#include <QTimer>

#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace bm {
class Bomberman;
class Explosion;
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
    void addBot(const std::shared_ptr<Bot>& bot);

    void addCellItem(std::unique_ptr<SpriteGraphicsObject> item);
    void addCharacterItem(std::unique_ptr<SpriteGraphicsObject> item);

    bool setCellItem(CellItem* item, size_t index);
    void addMovingObject(const std::shared_ptr<MovingObject>& object, std::unique_ptr<CharacterGraphicsItem> item);
    void destroyItemForObject(const std::shared_ptr<MovingObject>& object);
    void removeAllObjects();

public slots:
    void onCharacterStartedMove(const std::shared_ptr<Character>& character);
    void onCharacterStopped(const std::shared_ptr<Character>& character);
    void onCharacterMoved(const std::shared_ptr<MovingObject>& character);
    void onBombPlaced(const std::shared_ptr<Bomb>& bomb);
    void onBombExploded(const std::shared_ptr<Bomb>& bomb);
    void onExplosionHappened(const std::shared_ptr<Explosion>& explosion);
    void onExplosionFinished(const std::shared_ptr<Explosion>& explosion);

    void cellChanged(size_t index);

private slots:
    void updateAnimations();
    void addAnimation(bm::gui::SpriteGraphicsObject* sprite);
    void removeAnimation(bm::gui::SpriteGraphicsObject* sprite);

private:
    QPoint mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const;

private:
    std::shared_ptr<Map>               map_;
    std::vector<SpriteGraphicsObject*> cellItems_;
    using CharacterMap = std::unordered_map<std::shared_ptr<Character>, SpriteGraphicsObject*>;
    CharacterMap                                           characterMap_;
    std::unordered_map<GameObject*, SpriteGraphicsObject*> objects_;
    using ExplosionPartsMap = std::unordered_map<SpriteGraphicsObject*, std::vector<QGraphicsItem*>>;
    ExplosionPartsMap explosionParts_;

    SpriteObjectFactory                       spriteFactory_;
    QTimer                                    animationTimer_;
    std::unordered_set<SpriteGraphicsObject*> animations_;
    const std::chrono::milliseconds           animationPeriod_ { 100 };

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
