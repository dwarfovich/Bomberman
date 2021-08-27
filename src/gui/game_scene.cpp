#include "game_scene.hpp"
#include "sprite_graphics_object.hpp"
//#include "game/character.hpp"
#include "game/map.hpp"
#include "game/map_constants.hpp"
#include "game/moving_object.hpp"

#include <QPropertyAnimation>

#include <QDebug>
#define DEB qDebug()

namespace bm {
namespace gui {

GameScene::GameScene(QObject* parent) : QGraphicsScene { parent }, cellSize_ { 50 }
{}

void GameScene::setMap(const std::shared_ptr<Map>& map)
{
    const auto& cells = map->cells();
    for (const auto& cell : cells) {
        auto        cellItem = spriteFactory_.createCellObject(&cell);
        const auto& location = map->indexToLocation(cell.index());
        cellItem->setX(location.x() * cellSize);
        cellItem->setY(location.y() * cellSize);
        cellItems_.push_back(cellItem.get());

        QGraphicsScene::addItem(cellItem.release());
    }
}

void GameScene::addBomberman(const std::shared_ptr<Bomberman>& bomberman)
{
    auto item = spriteFactory_.createBombermanObject(bomberman);
    item->setPos(mapCoordinatesToSceneCoordinates(bomberman->coordinates()));
    characterMap_.emplace(bomberman, item.get());
    QGraphicsScene::addItem(item.release());
}

void GameScene::addCellItem(std::unique_ptr<SpriteGraphicsObject> item)
{
    //    if (item->isAnimatedDestroy()){
    //        auto* itemRawPtr = item.get();
    //        auto propertyAnimation = new QPropertyAnimation { itemRawPtr, "SpriteFrame" };
    //        propertyAnimation->setDuration(1000);
    //        propertyAnimation->setStartValue(0);
    //        propertyAnimation->setEndValue(itemRawPtr->framesCount());
    //        connect(propertyAnimation, &QPropertyAnimation::destroyed, this, [this, itemRawPtr]() {
    //            removeItem(itemRawPtr);
    //        });
    //        propertyAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    //    }

    QGraphicsScene::addItem(item.release());
}

void GameScene::addCharacterItem(std::unique_ptr<SpriteGraphicsObject> item)
{}

bool GameScene::setCellItem(CellItem* item, size_t index)
{
    try {
        if (index >= cellItems_.size()) {
            cellItems_.resize(index + 1);
        }
        cellItems_[index] = item;
        QGraphicsScene::addItem(cellItems_[index]);

        return true;
    } catch (...) {
        return false;
    }
}

void GameScene::addMovingObject(const std::shared_ptr<MovingObject>&   character,
                                std::unique_ptr<CharacterGraphicsItem> item)
{
    QGraphicsScene::addItem(item.get());
    movingObjects_.insert({ character, std::move(item) });
    onCharacterMoved(character);
}

void GameScene::destroyItemForObject(const std::shared_ptr<MovingObject>& object)
{
    movingObjects_.erase(object);
}

void GameScene::removeAllObjects()
{
    movingObjects_.clear();
    // TODO: free CellItems' memory.
    cellItems_.clear();
    clear();
}

void GameScene::onCharacterMoved(const std::shared_ptr<MovingObject>& charac)
{
    auto character = std::dynamic_pointer_cast<Character>(charac);
    auto iter      = characterMap_.find(character);
    if (iter != characterMap_.cend()) {
        iter->second->setPos(mapCoordinatesToSceneCoordinates(character->movementData().coordinates));
        iter->second->updateSpriteMapRow();
    }
    //    auto iter = movingObjects_.find(character);
    //    if (iter != movingObjects_.cend()) {
    //        iter->second->setPos(mapCoordinatesToSceneCoordinates(character->movementData().coordinates));
    //    }
}

void GameScene::cellChanged(size_t index)
{
    if (index < cellItems_.size()) {
        cellItems_[index]->update();
    }
}

// TODO: Check transformations in case of different cellSizes in bm:: and bm::gui::.
QPoint GameScene::mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const
{
    auto   xCells      = coordinates.x() / cellSize;
    auto   dx          = coordinates.x() - xCells * cellSize;
    auto   dxPercents  = (dx * 100.) / cellSize;
    QPoint sceneCoords = { xCells * cellSize_ - cellHalfSize + int(cellSize_ * dxPercents / 100.), 0 };

    auto yCells     = coordinates.y() / cellSize;
    auto dy         = coordinates.y() - yCells * cellSize;
    auto dyPercents = (dy * 100.) / cellSize;
    sceneCoords.setY(yCells * cellSize_ - cellHalfSize + int(cellSize_ * dyPercents / 100.));

    return sceneCoords;
}

} // namespace gui
} // namespace bm
