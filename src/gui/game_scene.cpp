#include "game_scene.hpp"
#include "sprite_graphics_object.hpp"
//#include "game/character.hpp"
#include "game/map.hpp"
#include "game/map_constants.hpp"
#include "game/moving_object.hpp"
#include "game/bomb.hpp"

#include <QPropertyAnimation>

#include <QDebug>
#define DEB qDebug()

namespace bm {
namespace gui {

GameScene::GameScene(QObject* parent) : QGraphicsScene { parent }, cellSize_ { 50 }
{
    connect(&animationTimer_, &QTimer::timeout, this, &GameScene::updateAnimations);
    animationTimer_.start(animationPeriod_);
}

void GameScene::setMap(const std::shared_ptr<Map>& map)
{
    map_ = map;

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
    objects_.insert({ bomberman.get(), item.get() });
    connect(item.get(), &SpriteGraphicsObject::startAnimation, this, &GameScene::addAnimation);
    connect(item.get(), &SpriteGraphicsObject::stopAnimation, this, &GameScene::removeAnimation);
    QGraphicsScene::addItem(item.release());
}

void GameScene::addBot(const std::shared_ptr<Bot>& bot)
{
    auto item = spriteFactory_.createBotObject(bot);
    item->setPos(mapCoordinatesToSceneCoordinates(bot->coordinates()));
    characterMap_.emplace(bot, item.get());
    objects_.insert({ bot.get(), item.get() });
    connect(item.get(), &SpriteGraphicsObject::startAnimation, this, &GameScene::addAnimation);
    connect(item.get(), &SpriteGraphicsObject::stopAnimation, this, &GameScene::removeAnimation);
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

void GameScene::onCharacterStartedMove(const std::shared_ptr<Character>& character)
{
    // characterMap_[character]->setCurrentFrame(
    auto iter = characterMap_.find(character);
    if (iter != characterMap_.cend()) {
        animations_.insert(iter->second);
    }
    //    updateAnimations();
}

void GameScene::onCharacterStopped(const std::shared_ptr<Character>& character)
{
    characterMap_[character]->setCurrentFrame(0);
    auto iter = characterMap_.find(character);
    if (iter != characterMap_.cend()) {
        animations_.erase(iter->second);
    }
    // updateAnimations();
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

void GameScene::onBombPlaced(const std::shared_ptr<Bomb>& bomb)
{
    auto        item           = spriteFactory_.createBombObject(bomb);
    const auto& mapCoordinates = map_->indexToCellCenterCoordinates(bomb->cellIndex);
    item->setPos(mapCoordinatesToSceneCoordinates(mapCoordinates));
    addAnimation(item.get());
    objects_.insert({ bomb.get(), item.get() });
    QGraphicsScene::addItem(item.release());
}

void GameScene::onBombExploded(const std::shared_ptr<Bomb>& bomb)
{
    auto bombItem = objects_.find(bomb.get());
    animations_.erase(bombItem->second);

    QGraphicsScene::removeItem(bombItem->second);
    objects_.erase(bombItem);
}

void GameScene::onExplosionHappened(const std::shared_ptr<Explosion>& explosion)
{
    auto explosionObject = spriteFactory_.createExplosionObject(explosion.get(), *map_.get());
    explosionObject->setPos(map_->locationToCellCenterCoordinates(explosion->center()));
    explosionObject->setX(explosionObject->x() - cellHalfSize);
    explosionObject->setY(explosionObject->y() - cellHalfSize);
    objects_.emplace(explosion.get(), explosionObject.get());
    animations_.insert(explosionObject.get());
    for (auto* child : explosionObject->childItems()) {
        addItem(child);
        animations_.insert(static_cast<SpriteGraphicsObject*>(child));
        explosionParts_[explosionObject.get()].push_back(child);
    }
    explosionObject->setCurrentFrame(0);
    addItem(explosionObject.release());

    //    auto t = spriteFactory_.createBotObject(characterMap_.cbegin()->first);
}

void GameScene::onExplosionFinished(const std::shared_ptr<Explosion>& explosion)
{
    auto explosionIter = objects_.find(explosion.get());
    if (explosionIter != objects_.cend()) {
        auto* centerObject = explosionIter->second;
        auto  partsIter    = explosionParts_.find(centerObject);
        if (partsIter != explosionParts_.cend()) {
            for (auto* part : partsIter->second) {
                animations_.erase(static_cast<SpriteGraphicsObject*>(part));
                removeItem(part);
            }
            explosionParts_.erase(partsIter);
        }

        animations_.erase(centerObject);
        objects_.erase(explosionIter);
        removeItem(centerObject);
        delete centerObject;
    }
}

void GameScene::onObjectDestroyed(std::shared_ptr<GameObject> object)
{
    auto objectIter = objects_.find(object.get());
    if (objectIter != objects_.cend()) {
        if (objectIter->second->isAnimated()) {
            objectIter->second->setDestroyAnimationFinishedCallback(
                std::bind(&GameScene::destroyAniimationFinished, this, std::placeholders::_1));
            objectIter->second->startDestroyAnimation();
        } else {
            auto explosionIter = explosionParts_.find(objectIter->second);
            if (explosionIter != explosionParts_.cend()) {
                explosionParts_.erase(explosionIter);
            }
            objects_.erase(objectIter);
            removeItem(objectIter->second);
        }
    }
}

void GameScene::cellChanged(size_t index)
{
    if (index < cellItems_.size()) {
        cellItems_[index]->update();
    }
}

void GameScene::updateAnimations()
{
    for (auto* sprite : animations_) {
        sprite->advance(1);
    }

    for (auto* sprite : animationsToDelete_) {
        // TODO: Remove sprite for Characters.
        auto explosionIter = explosionParts_.find(sprite);
        if (explosionIter != explosionParts_.cend()) {
            explosionParts_.erase(explosionIter);
        }
        // TODO: refactor searching for GameObject*.
        for (const auto& [gameObject, objectSprite] : objects_) {
            if (objectSprite == sprite) {
                objects_.erase(gameObject);
                break;
            }
        }

        animations_.erase(sprite);
        removeItem(sprite);
    }

    animationsToDelete_.clear();
}

void GameScene::addAnimation(bm::gui::SpriteGraphicsObject* sprite)
{
    animations_.insert(sprite);
}

void GameScene::removeAnimation(bm::gui::SpriteGraphicsObject* sprite)
{
    sprite->setCurrentFrame(0);
    animations_.erase(sprite);
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

void GameScene::destroyAniimationFinished(SpriteGraphicsObject* sprite)
{
    animationsToDelete_.push_back(sprite);
}

} // namespace gui
} // namespace bm
