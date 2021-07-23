#include "bomb_explosion.hpp"
#include "map.hpp"
#include "map_constants.hpp"

namespace bm {

BombExplosionResult explodeBomb(Map &map, Bomb &bomb)
{
    if (!map.removeBomb(bomb.cellIndex)) {
        return {};
    }

    std::vector<GameObject *> affectedObjects;

    const auto index      = bomb.cellIndex;
    auto       centerCell = map.indexToLocation(index);
    size_t     firstX     = centerCell.x() - bomb->radius >= 0 ? centerCell.x() - bomb->radius : 0;
    size_t lastX = centerCell.x() + bomb->radius >= widthInCells_ ? widthInCells_ - 1 : centerCell.x() + bomb->radius;
    auto   currentCell = centerCell;
    while (currentCell.x() >= firstX) {
        addGameObjectsForCell(currentCell, affectedObjects);
        if (!cellIsMovable(currentCell)) {
            break;
        }
        currentCell.setX(currentCell.x() - 1);
    }
    currentCell = centerCell;
    currentCell.setX(currentCell.x() + 1);
    for (; currentCell.x() <= lastX; currentCell.setX(currentCell.x() + 1)) {
        addGameObjectsForCell(currentCell, affectedObjects);
        if (!cellIsMovable(currentCell)) {
            break;
        }
    }

    //    size_t firstY = centerCell.y() - bomb->radius >= 0 ? centerCell.y() - bomb->radius : 0;
    //    size_t lastY = centerCell.y() + bomb->radius >= heightInCells_ ? heightInCells_ - 1 : centerCell.y() +
    //    bomb->radius; currentCell  = centerCell; currentCell.setY(currentCell.y() - 1); for (; currentCell.y() >=
    //    firstY; currentCell.setY(currentCell.y() - 1)) {
    //        addGameObjectsForCell(currentCell, affectedObjects);
    //        if (!cellIsMovable(currentCell)) {
    //            break;
    //        }
    //    }

    //    currentCell = centerCell;
    //    currentCell.setY(currentCell.y() + 1);
    //    for (; currentCell.y() <= lastY; currentCell.setY(currentCell.y() + 1)) {
    //        addGameObjectsForCell(currentCell, affectedObjects);
    //        if (!cellIsMovable(currentCell)) {
    //            break;
    //        }
    //    }

    //    return affectedObjects;
}

BombExplosionResult::BombExplosionResult()
    : explosion { { invalidMapIndex, invalidMapIndex }, { invalidMapIndex, invalidMapIndex } }, affectedObjects {}
{}

} // namespace bm
