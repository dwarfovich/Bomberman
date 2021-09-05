#ifndef GAMESCENE_HPP
#define GAMESCENE_HPP

#include "sprite_item_callbacks.hpp"
#include "sprite_factory.hpp"

#include <QGraphicsScene>
#include <QTimer>

#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace bm {
class GameObject;
class Bomberman;
class Explosion;
class Character;
class Map;

namespace gui {

class GameScene : public QGraphicsScene
{
    friend class SpriteItemCallbacks;

public:
    explicit GameScene(QObject* parent = nullptr);

    void setMap(const std::shared_ptr<Map>& map);
    void addBomberman(const std::shared_ptr<Bomberman>& bomberman);
    void addBot(const std::shared_ptr<Bot>& bot);

public slots:
    void onCharacterStartedMove(const std::shared_ptr<Character>& character);
    void onCharacterStopped(const std::shared_ptr<Character>& character);
    void onCharacterMoved(const std::shared_ptr<Character>& character);
    void onBombPlaced(const std::shared_ptr<Bomb>& bomb);
    void onBombExploded(const std::shared_ptr<Bomb>& bomb);
    void onExplosionHappened(const std::shared_ptr<Explosion>& explosion);
    void onExplosionFinished(const std::shared_ptr<Explosion>& explosion);
    void onObjectDestroyed(std::shared_ptr<GameObject> object);
    void cellChanged(size_t index);

private slots:
    void updateAnimations();

private:
    void   addAnimation(SpriteItem* sprite);
    QPoint mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const;
    void   destroyAnimationFinished(SpriteItem* item);

private:
    SpriteItemCallbacks                                          callbacks_;
    SpriteObjectFactory                                          spriteFactory_;
    std::shared_ptr<Map>                                         map_;
    std::vector<CellSpriteItem*>                                 cellItems_;
    std::unordered_map<std::shared_ptr<GameObject>, SpriteItem*> gameObjects_;
    std::unordered_set<SpriteItem*>                              spriteItems_;
    std::unordered_set<SpriteItem*>                              animations_;
    std::vector<SpriteItem*>                                     animationsToDelete_;
    QTimer                                                       animationTimer_;
    const std::chrono::milliseconds                              animationPeriod_ { 100 };
};

} // namespace gui
} // namespace bm

#endif // GAMESCENE_HPP
