#include "game_scene.hpp"
#include "cell_sprite_item.hpp"
#include "explosion_sprite_item.hpp"
#include "sprite_item.hpp"
#include "game/map.hpp"
#include "game/map_constants.hpp"
#include "game/bomb.hpp"

#include <QPropertyAnimation>

#include <QDebug>
#define DEB qDebug()

namespace bm {
namespace gui {

GameScene::GameScene(QObject* parent) : QGraphicsScene { parent }, callbacks_ { this }, spriteFactory_ { &callbacks_ }
{
    connect(&animationTimer_, &QTimer::timeout, this, &GameScene::updateAnimations);
    animationTimer_.start(animationPeriod_);
}

void GameScene::setMap(const std::shared_ptr<Map>& map)
{
    map_ = map;

    const auto& cells = map->cells();
    for (const auto& cell : cells) {
        auto cellItem = spriteFactory_.createSprite(cell.get());
        if (cellItem) {
            const auto& location = map->indexToLocation(cell->index());
            cellItem->setX(location.x() * cellSize);
            cellItem->setY(location.y() * cellSize);
            cellItems_.push_back(cellItem.get());

            QGraphicsScene::addItem(cellItem.release());
        }
    }

    for (const auto& [bomberman, bombermanSptr] : map->bombermans()) {
        addBomberman(bombermanSptr);
    }

    for (const auto& bot : map->bots()) {
        addBot(bot);
    }
}

void GameScene::addBomberman(const std::shared_ptr<Bomberman>& bomberman)
{
    auto item = spriteFactory_.createSprite(bomberman);
    item->setPos(mapCoordinatesToSceneCoordinates(bomberman->coordinates()));
    spriteItems_.insert(item.get());
    gameObjects_.emplace(bomberman, item.get());
    QGraphicsScene::addItem(item.release());
}

void GameScene::addBot(const std::shared_ptr<Bot>& bot)
{
    auto item = spriteFactory_.createSprite(bot);
    item->setPos(mapCoordinatesToSceneCoordinates(bot->coordinates()));
    spriteItems_.insert(item.get());
    gameObjects_.emplace(bot, item.get());
    addAnimation(item.get());
    QGraphicsScene::addItem(item.release());
}

void GameScene::onCharacterStartedMove(const std::shared_ptr<Character>& character)
{
    auto itemIter = gameObjects_.find(character);
    if (itemIter != gameObjects_.cend()) {
        addAnimation(itemIter->second);
        itemIter->second->updateSprite();
    }
}

void GameScene::onCharacterStopped(const std::shared_ptr<Character>& character)
{
    auto itemIter = gameObjects_.find(character);
    if (itemIter != gameObjects_.cend()) {
        animations_.erase(itemIter->second);
        itemIter->second->setCurrentFrame(0);
        itemIter->second->updateSprite();
    }
}

void GameScene::onCharacterMoved(const std::shared_ptr<Character>& character)
{
    auto iter = gameObjects_.find(character);
    if (iter != gameObjects_.cend()) {
        iter->second->setPos(mapCoordinatesToSceneCoordinates(character->movementData().coordinates));
    }
}

void GameScene::onBombPlaced(const std::shared_ptr<Bomb>& bomb)
{
    auto        item           = spriteFactory_.createSprite(bomb);
    const auto& mapCoordinates = map_->indexToCellCenterCoordinates(bomb->cellIndex);
    item->setPos(mapCoordinatesToSceneCoordinates(mapCoordinates));
    addAnimation(item.get());
    gameObjects_.insert({ bomb, item.get() });
    QGraphicsScene::addItem(item.release());
}

void GameScene::onBombExploded(const std::shared_ptr<Bomb>& bomb)
{
    auto bombIter = gameObjects_.find(bomb);
    if (bombIter != gameObjects_.cend()) {
        animations_.erase(bombIter->second);
        QGraphicsScene::removeItem(bombIter->second);
        gameObjects_.erase(bombIter);
    }
}

void GameScene::onExplosionHappened(const std::shared_ptr<Explosion>& explosion)
{
    auto item = spriteFactory_.createSprite(explosion.get(), *map_.get());
    item->setPos(map_->locationToCellCenterCoordinates(explosion->center()));
    item->setX(item->x() - sprite_ns::cellHalfSize);
    item->setY(item->y() - sprite_ns::cellHalfSize);
    gameObjects_.emplace(explosion, item.get());
    animations_.insert(item.get());
    QGraphicsScene::addItem(item.release());
}

void GameScene::onExplosionFinished(const std::shared_ptr<Explosion>& explosion)
{
    auto explosionIter = gameObjects_.find(explosion);
    if (explosionIter != gameObjects_.cend()) {
        animations_.erase(explosionIter->second);
        removeItem(explosionIter->second);
        gameObjects_.erase(explosionIter);
    }
}

void GameScene::onObjectDestroyed(std::shared_ptr<GameObject> object)
{
    auto itemIter = gameObjects_.find(object);
    if (itemIter == gameObjects_.cend()) {
        return;
    }

    auto* sprite = itemIter->second;
    gameObjects_.erase(itemIter);
    if (sprite->hasDestroyAnimation()) {
        animations_.insert(sprite);
        sprite->startDestroyAnimation();
    } else {
        animations_.erase(sprite);
        removeItem(sprite);
    }

    spriteItems_.erase(sprite);
}

void GameScene::onCellStructureChanged(size_t index, CellStructure previousStructure)
{
    if (index < cellItems_.size()) {
        if (previousStructure == CellStructure::Bricks) {
            cellItems_[index]->setAnimationType(CellSpriteItem::AnimationType::BricksDestroying);
        } else if (previousStructure == CellStructure::Concrete) {
            cellItems_[index]->setAnimationType(CellSpriteItem::AnimationType::ConcreteToBricksDestroying);
        }
        animations_.insert(cellItems_[index]);
    }
}

void GameScene::onModifierAdded(size_t index, const std::shared_ptr<IModifier>& modifier)
{
    auto item = spriteFactory_.createSprite(index, modifier);
    item->setPos(map_->indexToCoordinates(index));
    auto inserted = gameObjects_.emplace(modifier, item.get());
    spriteItems_.insert(item.get());
    animations_.insert(item.get());
    QGraphicsScene::addItem(item.release());
}

void GameScene::onExitRevealed(size_t index)
{
    auto exitSprite = spriteFactory_.createExitSprite();
    exitSprite->setPos(map_->indexToCoordinates(index));
    exitSprite_ = exitSprite.get();
    addItem(exitSprite.release());
}

void GameScene::onExitActivated()
{
    addAnimation(exitSprite_);
}

void GameScene::onModifierRemoved(size_t index, const std::shared_ptr<IModifier>& modifier)
{
    auto iter = gameObjects_.find(modifier);
    if (iter != gameObjects_.cend()) {
        animations_.erase(iter->second);
        spriteItems_.erase(iter->second);
        removeItem(iter->second);
        gameObjects_.erase(iter);
    }
}

void GameScene::updateAnimations()
{
    for (auto* sprite : animations_) {
        sprite->advance(1);
    }

    deleteFinishedAnimations();
}

void GameScene::addAnimation(SpriteItem* sprite)
{
    animations_.insert(sprite);
    if (!animationTimer_.isActive()) {
        animationTimer_.start(animationPeriod_);
    }
}

// TODO: Check transformations in case of different cellSizes in bm:: and bm::gui::.
QPoint GameScene::mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const
{
    auto   xCells      = coordinates.x() / cellSize;
    auto   dx          = coordinates.x() - xCells * cellSize;
    auto   dxPercents  = (dx * 100.) / cellSize;
    QPoint sceneCoords = { xCells * sprite_ns::cellSize - cellHalfSize + int(sprite_ns::cellSize * dxPercents / 100.),
                           0 };

    auto yCells     = coordinates.y() / cellSize;
    auto dy         = coordinates.y() - yCells * cellSize;
    auto dyPercents = (dy * 100.) / cellSize;
    sceneCoords.setY(yCells * sprite_ns::cellSize - cellHalfSize + int(sprite_ns::cellSize * dyPercents / 100.));

    return sceneCoords;
}

void GameScene::destroyAnimationFinished(SpriteItem* item)
{
    Q_ASSERT(item);

    animationsToDelete_.push_back({ item, true });
}

void GameScene::animationFinished(SpriteItem* item)
{
    Q_ASSERT(item);

    animationsToDelete_.push_back({ item, false });
}

void GameScene::deleteFinishedAnimations()
{
    for (const auto& [sprite, shouldRemoveItem] : animationsToDelete_) {
        animations_.erase(sprite);
        if (shouldRemoveItem) {
            removeItem(sprite);
        }
    }
    animationsToDelete_.clear();
}

} // namespace gui
} // namespace bm
