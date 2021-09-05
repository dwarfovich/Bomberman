#include "sprite_factory.hpp"
#include "sprite_item.hpp"
#include "cell_sprite_item.hpp"
#include "character_sprite_item.hpp"
#include "explosion_sprite_item.hpp"
#include "game/character.hpp"
#include "game/bomberman.hpp"
#include "game/bot.hpp"
#include "game/explosion.hpp"
#include "game/map.hpp"
#include "game/cell_location.hpp"

namespace bm {
namespace gui {

SpriteObjectFactory::SpriteObjectFactory(const SpriteItemCallbacks *const callbacks) : callbacks_ { callbacks }
{
    cell_      = QPixmap { QStringLiteral(":/gfx/cell.png") };
    bomberman_ = QPixmap { QStringLiteral(":/gfx/bomberman.png") };
    bot_       = QPixmap { QStringLiteral(":/gfx/bot.png") };
    bomb_      = QPixmap { QStringLiteral(":/gfx/bomb.png") };
    explosion_ = QPixmap { QStringLiteral(":/gfx/explosion - Copy.png") };
}

std::unique_ptr<CellSpriteItem> SpriteObjectFactory::createSprite(const Cell *cell)
{
    auto item = std::make_unique<CellSpriteItem>(callbacks_, cell_);
    if (cell->structure() == CellStructure::Empty) {
        item->setStructureFrame(CellSpriteItem::CellStructureFrame::Empty);
    } else if (cell->structure() == CellStructure::Bricks) {
        item->setStructureFrame(CellSpriteItem::CellStructureFrame::Bricks);
    } else if (cell->structure() == CellStructure::Concrete) {
        item->setStructureFrame(CellSpriteItem::CellStructureFrame::Concrete);
    }

    return item;
}

std::unique_ptr<SpriteItem> SpriteObjectFactory::createSprite(const std::shared_ptr<Bomberman> &character)
{
    auto item = std::make_unique<CharacterSpriteItem>(callbacks_, bomberman_);
    item->setCharacter(character);
    item->setFramesCount(10);

    return item;
}

std::unique_ptr<SpriteItem> SpriteObjectFactory::createSprite(const std::shared_ptr<Bot> &character)
{
    auto item = std::make_unique<CharacterSpriteItem>(callbacks_, bot_);
    item->setCharacter(character);
    item->setFramesCount(10);

    return item;
}

std::unique_ptr<SpriteItem> SpriteObjectFactory::createSprite(const std::shared_ptr<Bomb> &bomb)
{
    auto item = std::make_unique<SpriteItem>(callbacks_, bomb_);
    item->setFramesCount(4);

    return item;
}

std::unique_ptr<ExplosionSpriteItem> SpriteObjectFactory::createSprite(const Explosion *explosion,
                                                                       const Map &      map,
                                                                       const QPoint &   centerCoordinates)
{
    auto item = std::make_unique<ExplosionSpriteItem>(callbacks_, explosion_);
    item->setPixmap(explosion_);
    item->setFramesCount(4);
    item->setPos(centerCoordinates);

    for (size_t x = explosion->xMin(); x <= explosion->xMax(); ++x) {
        auto centerY = explosion->center().y();
        if (explosion->center() == CellLocation { x, centerY }) {
            continue;
        }

        auto child = std::make_unique<SpriteItem>(callbacks_, explosion_);
        if (x == explosion->xMin()) {
            child->setCurrentSpriteRow(ExplosionSpriteItem::PartType::LeftHorizontalEnding);
        } else if (x == explosion->xMax()) {
            child->setCurrentSpriteRow(ExplosionSpriteItem::PartType::RightHorizontalEnding);
        } else {
            child->setCurrentSpriteRow(ExplosionSpriteItem::PartType::Horizontal);
        }
        child->setFramesCount(4);
        child->setX(item->x()
                    + sprite_ns::cellSize * (static_cast<int>(x) - static_cast<int>(explosion->center().x())));
        child->setY(item->y());
        item->addExplosionPart(std::move(child));
    }

    for (size_t y = explosion->yMin(); y <= explosion->yMax(); ++y) {
        auto centerX = explosion->center().x();
        if (explosion->center() == CellLocation { centerX, y }) {
            continue;
        }

        auto child = std::make_unique<SpriteItem>(callbacks_, explosion_);
        if (y == explosion->yMin()) {
            child->setCurrentSpriteRow(ExplosionSpriteItem::PartType::TopVerticalEnding);
        } else if (y == explosion->yMax()) {
            child->setCurrentSpriteRow(ExplosionSpriteItem::PartType::BottomVerticalEnding);
        } else {
            child->setCurrentSpriteRow(ExplosionSpriteItem::PartType::Vertical);
        }
        child->setFramesCount(4);
        child->setX(item->x());
        child->setY(item->y()
                    + sprite_ns::cellSize * (static_cast<int>(y) - static_cast<int>(explosion->center().y())));
        item->addExplosionPart(std::move(child));
    }

    return item;
}

// std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createCellObject(const Cell *cell)
//{
//    //    auto item = std::make_unique<CellItem>(cell);

//    //    return item;
//    return nullptr;
//}

// std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBombermanObject(
//    const std::shared_ptr<Bomberman> &character)
//{
//    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
//    item->setPixmap(bomberman_);
//    item->setCharacter(character);

//    return item;
//}

// std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBotObject(const std::shared_ptr<Bot> &character)
//{
//    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
//    item->setPixmap(bot_);
//    item->setCharacter(character);
//    item->setDestroyAnimationSpriteRow(4);

//    return item;
//}

// std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBombObject(const std::shared_ptr<Bomb> &bomb)
//{
//    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
//    item->setPixmap(bomb_);
//    item->setFramesCount(4);

//    return item;
//}

// std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createExplosionObject(const Explosion *explosion,
//                                                                                 const Map &      map,

//                                                                                 const QPoint &centerCoordinates)
//{
//    //    auto item = std::make_unique<ExplosionGraphicsObject>(nullptr, explosion);
//    //    item->setPixmap(explosion_);
//    //    item->setFramesCount(4);
//    //    item->setPos(centerCoordinates);

//    //    std::vector<ExplosionGraphicsObject *> children;
//    //    for (size_t x = explosion->xMin(); x <= explosion->xMax(); ++x) {
//    //        auto centerY = explosion->center().y();
//    //        if (explosion->center() == CellLocation { x, centerY }) {
//    //            continue;
//    //        }

//    //        auto child = new ExplosionGraphicsObject { item.get() };
//    //        child->setPixmap(explosion_);
//    //        if (x == explosion->xMin()) {
//    //            child->setExplosionPart(ExplosionPart::LeftHorizontalEnd);
//    //        } else if (x == explosion->xMax()) {
//    //            child->setExplosionPart(ExplosionPart::RightHorizontalEnd);
//    //        } else {
//    //            child->setExplosionPart(ExplosionPart::Horizontal);
//    //        }
//    //        child->setFramesCount(4);
//    //        child->setPos(mapCoordinatesToSceneCoordinates(map.locationToCellCenterCoordinates({ x, centerY })));
//    //        children.push_back(child);
//    //    }

//    //    for (size_t y = explosion->yMin(); y <= explosion->yMax(); ++y) {
//    //        auto centerX = explosion->center().x();
//    //        if (explosion->center() == CellLocation { centerX, y }) {
//    //            continue;
//    //        }

//    //        auto child = new ExplosionGraphicsObject { item.get() };
//    //        child->setPixmap(explosion_);
//    //        if (y == explosion->yMin()) {
//    //            child->setExplosionPart(ExplosionPart::TopVerticalEnd);
//    //        } else if (y == explosion->yMax()) {
//    //            child->setExplosionPart(ExplosionPart::BottomVerticalEnd);
//    //        } else {
//    //            child->setExplosionPart(ExplosionPart::Vertical);
//    //        }
//    //        child->setFramesCount(4);
//    //        child->setPos(mapCoordinatesToSceneCoordinates(map.locationToCellCenterCoordinates({ centerX, y })));
//    //        children.push_back(child);
//    //    }

//    //    item->setParts(children);

//    //    return item;

//    return nullptr;
//}

QPoint SpriteObjectFactory::mapCoordinatesToSceneCoordinates(const QPoint &coordinates) const
{
    using namespace sprite_ns;
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
