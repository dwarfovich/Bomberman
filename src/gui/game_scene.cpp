#include "game_scene.hpp"
//#include "game/character.hpp"
#include "game/map_constants.hpp"
#include "game/moving_object.hpp"

namespace bm {
namespace gui {

GameScene::GameScene(QObject* parent) : QGraphicsScene { parent }, cellSize_ { 50 }
{}

bool GameScene::setCellItem(CellItem* item, size_t index)
{
    try {
        if (index >= cellItems_.size()) {
            cellItems_.resize(index + 1);
        }
        cellItems_[index] = item;
        addItem(cellItems_[index]);

        return true;
    } catch (...) {
        return false;
    }
}

void GameScene::addMovingObject(const std::shared_ptr<MovingObject>&   character,
                             std::unique_ptr<CharacterGraphicsItem> item)
{
    addItem(item.get());
    movingObjects_.insert({ character, std::move(item) });
    onCharacterMoved(character);
}

void GameScene::destroyItemForObject(const std::shared_ptr<MovingObject> &object)
{
    movingObjects_.erase(object);
}

void GameScene::onCharacterMoved(const std::shared_ptr<MovingObject>& character)
{
    auto iter = movingObjects_.find(character);
    if (iter != movingObjects_.cend()) {
        iter->second->setPos(mapCoordinatesToSceneCoordinates(character->movementData().coordinates));
    }
}

void GameScene::cellChanged(size_t index)
{
    if (index < cellItems_.size()) {
        cellItems_[index]->update();
    }
}

QPoint GameScene::mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const
{
    auto   xCells      = coordinates.x() / cellSize;
    auto   dx          = coordinates.x() - xCells * cellSize;
    auto   dxPercents  = (dx * 100.) / cellSize;
    QPoint sceneCoords = { xCells * cellSize_ + int(cellSize_ * dxPercents / 100.), 0 };

    auto yCells     = coordinates.y() / cellSize;
    auto dy         = coordinates.y() - yCells * cellSize;
    auto dyPercents = (dy * 100.) / cellSize;
    sceneCoords.setY(yCells * cellSize_ + int(cellSize_ * dyPercents / 100.));

    return sceneCoords;
}

} // namespace gui
} // namespace bm
