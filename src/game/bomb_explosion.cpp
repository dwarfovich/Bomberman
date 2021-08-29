#include "bomb_explosion.hpp"
#include "map.hpp"
#include "map_constants.hpp"

namespace bm {

namespace {

std::unique_ptr<Explosion> calculateExplosion(const Map &map, const Bomb &bomb)
{
    const auto centerCell = map.indexToLocation(bomb.cellIndex);

    size_t firstX = centerCell.x() >= bomb.radius ? centerCell.x() - bomb.radius : 0;
    size_t lastX  = centerCell.x() + bomb.radius >= map.width() ? map.width() - 1 : centerCell.x() + bomb.radius;

    std::pair<size_t, size_t> xRange { firstX, lastX };
    for (auto currentCell = CellLocation { firstX, centerCell.y() }; currentCell.x() < centerCell.x();
         currentCell.incrementX()) {
        if (!map.cellIsMovable(currentCell)) {
            xRange.first = currentCell.x();
        }
    }

    for (auto currentCell = centerCell; currentCell.x() <= lastX; currentCell.incrementX()) {
        if (!map.cellIsMovable(currentCell)) {
            xRange.second = currentCell.x();
            break;
        }
    }

    size_t firstY = centerCell.y() >= bomb.radius ? centerCell.y() - bomb.radius : 0;
    size_t lastY  = centerCell.y() + bomb.radius >= map.height() ? map.height() - 1 : centerCell.y() + bomb.radius;

    std::pair<size_t, size_t> yRange { firstY, lastY };
    for (auto currentCell = CellLocation { centerCell.x(), firstY }; currentCell.y() < centerCell.y();
         currentCell.incrementY()) {
        if (!map.cellIsMovable(currentCell)) {
            yRange.first = currentCell.y();
        }
    }

    for (auto currentCell = centerCell; currentCell.y() <= lastY; currentCell.incrementY()) {
        if (!map.cellIsMovable(currentCell)) {
            yRange.second = currentCell.y();
            break;
        }
    }

    return std::make_unique<Explosion>(centerCell, xRange, yRange);
}

} // namespace

BombExplosionResult::BombExplosionResult()
    : explosion { std::make_shared<Explosion>(invalidCellLocation,
                                              std::pair<size_t, size_t> { invalidMapIndex, invalidMapIndex },
                                              std::pair<size_t, size_t> { invalidMapIndex, invalidMapIndex }) }
    , affectedObjects {}
{}

BombExplosionResult::BombExplosionResult(const std::shared_ptr<Explosion> &aExplosion,
                                         const std::vector<GameObject *> & aAffectedObjects)
    : explosion { aExplosion }, affectedObjects { aAffectedObjects }
{}

// BombExplosionResult::BombExplosionResult(const Explosion &aExplosion, const std::vector<GameObject *>
// &aAffectedObjects)
//    : explosion { aExplosion }, affectedObjects { aAffectedObjects }
//{}

BombExplosionResult explodeBomb(Map &map, Bomb &bomb)
{
    if (!map.removeBomb(bomb.cellIndex)) {
        return {};
    }

    const auto &              bombLocation = map.indexToLocation(bomb.cellIndex);
    auto                      explosion    = calculateExplosion(map, bomb);
    std::vector<GameObject *> affectedObjects;
    for (size_t x = explosion->xMin(); x <= explosion->xMax(); ++x) {
        map.addGameObjectsForCell({ x, bombLocation.y() }, affectedObjects);
    }
    for (size_t y = explosion->yMin(); y < explosion->center().y(); ++y) {
        map.addGameObjectsForCell({ bombLocation.x(), y }, affectedObjects);
    }
    for (size_t y = explosion->center().y() + 1; y <= explosion->yMax(); ++y) {
        map.addGameObjectsForCell({ bombLocation.x(), y }, affectedObjects);
    }

    return { std::move(explosion), std::move(affectedObjects) };
}

} // namespace bm
