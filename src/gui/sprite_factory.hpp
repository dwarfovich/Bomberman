#ifndef BM_SPRITEFACTORY_HPP
#define BM_SPRITEFACTORY_HPP

#include "sprite_graphics_object.hpp"

#include <memory>

namespace bm {
class Cell;
class Bomberman;
class Bot;
struct Bomb;
class Explosion;
class Map;

namespace gui {

class SpriteObjectFactory
{
public:
    SpriteObjectFactory();

    std::unique_ptr<SpriteGraphicsObject> createCellObject(const Cell* cell);
    std::unique_ptr<SpriteGraphicsObject> createBombermanObject(const std::shared_ptr<Bomberman>& character);
    std::unique_ptr<SpriteGraphicsObject> createBotObject(const std::shared_ptr<Bot>& character);
    std::unique_ptr<SpriteGraphicsObject> createBombObject(const std::shared_ptr<Bomb>& bomb);
    std::unique_ptr<SpriteGraphicsObject> createExplosionObject(const Explosion* explosion,
                                                                const Map&       map,
                                                                const QPoint&    centerCoordinates = {});
    QPoint                                mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const;

private:
    QPixmap cell_;
    QPixmap bomberman_;
    QPixmap bot_;
    QPixmap bomb_;
    QPixmap explosion_;
};

// std::unique_ptr<SpriteGraphicsObject> createCellObject(const Cell *cell);

} // namespace gui
} // namespace bm

#endif // BM_SPRITEFACTORY_HPP
