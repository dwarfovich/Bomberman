#include "sprite_factory.hpp"
#include "cell_item.hpp"
#include "animated_sprite_graphics_object.hpp"
#include "explosion_graphics_object.hpp"
#include "game/character.hpp"
#include "game/bomberman.hpp"
#include "game/bot.hpp"
#include "game/explosion.hpp"
#include "game/map.hpp"
#include "game/cell_location.hpp"

namespace bm {
namespace gui {

SpriteObjectFactory::SpriteObjectFactory()
{
    bomberman_ = QPixmap { QStringLiteral(":/gfx/bomberman.png") };
    bot_       = QPixmap { QStringLiteral(":/gfx/bot.png") };
    bomb_      = QPixmap { QStringLiteral(":/gfx/bomb.png") };
    explosion_ = QPixmap { QStringLiteral(":/gfx/explosion.png") };
}

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createCellObject(const Cell *cell)
{
    auto item = std::make_unique<CellItem>(cell);

    return item;
}

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBombermanObject(
    const std::shared_ptr<Bomberman> &character)
{
    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
    item->setPixmap(bomberman_);
    item->setCharacter(character);

    return item;
}

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBotObject(const std::shared_ptr<Bot> &character)
{
    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
    item->setPixmap(bot_);
    item->setCharacter(character);
    item->setDestroyAnimationSpriteRow(4);

    return item;
}

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBombObject(const std::shared_ptr<Bomb> &bomb)
{
    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
    item->setPixmap(bomb_);
    item->setFramesCount(4);

    return item;
}

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createExplosionObject(const Explosion *explosion,
                                                                                 const Map &      map,

                                                                                 const QPoint &centerCoordinates)
{
    auto item = std::make_unique<ExplosionGraphicsObject>(nullptr, explosion);
    item->setPixmap(explosion_);
    item->setFramesCount(4);
    item->setPos(centerCoordinates);

    std::vector<ExplosionGraphicsObject *> children;
    for (size_t x = explosion->xMin(); x <= explosion->xMax(); ++x) {
        auto centerY = explosion->center().y();
        if (explosion->center() == CellLocation { x, centerY }) {
            continue;
        }

        auto child = new ExplosionGraphicsObject { item.get() };
        child->setPixmap(explosion_);
        if (x == explosion->xMin()) {
            child->setExplosionPart(ExplosionPart::LeftHorizontalEnd);
        } else if (x == explosion->xMax()) {
            child->setExplosionPart(ExplosionPart::RightHorizontalEnd);
        } else {
            child->setExplosionPart(ExplosionPart::Horizontal);
        }
        child->setFramesCount(4);
        child->setPos(mapCoordinatesToSceneCoordinates(map.locationToCellCenterCoordinates({ x, centerY })));
        children.push_back(child);
    }

    for (size_t y = explosion->yMin(); y <= explosion->yMax(); ++y) {
        auto centerX = explosion->center().x();
        if (explosion->center() == CellLocation { centerX, y }) {
            continue;
        }

        auto child = new ExplosionGraphicsObject { item.get() };
        child->setPixmap(explosion_);
        if (y == explosion->yMin()) {
            child->setExplosionPart(ExplosionPart::TopVerticalEnd);
        } else if (y == explosion->yMax()) {
            child->setExplosionPart(ExplosionPart::BottomVerticalEnd);
        } else {
            child->setExplosionPart(ExplosionPart::Vertical);
        }
        child->setFramesCount(4);
        child->setPos(mapCoordinatesToSceneCoordinates(map.locationToCellCenterCoordinates({ centerX, y })));
        children.push_back(child);
    }

    item->setParts(children);

    return item;
}

QPoint SpriteObjectFactory::mapCoordinatesToSceneCoordinates(const QPoint &coordinates) const
{
    auto   xCells      = coordinates.x() / cellSize;
    auto   dx          = coordinates.x() - xCells * cellSize;
    auto   dxPercents  = (dx * 100.) / cellSize;
    QPoint sceneCoords = { xCells * cellSize - cellHalfSize + int(cellSize * dxPercents / 100.), 0 };

    auto yCells     = coordinates.y() / cellSize;
    auto dy         = coordinates.y() - yCells * cellSize;
    auto dyPercents = (dy * 100.) / cellSize;
    sceneCoords.setY(yCells * cellSize - cellHalfSize + int(cellSize * dyPercents / 100.));

    return sceneCoords;
}

} // namespace gui
} // namespace bm
