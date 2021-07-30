#include "move_processor.hpp"
#include "map_constants.hpp"

namespace bm {

namespace {

int firstCoordinate(const QPoint& coordinates, Direction direction)
{
    if (direction == Direction::Upward || direction == Direction::Downward) {
        return coordinates.y();
    } else {
        return coordinates.x();
    }
}

int maxFirstCoordinateAdvance(int firstCoordinate, int firstCoordObstacle, Direction direction)
{
    if (direction == Direction::Upward || direction == Direction::Left) {
        return std::max(firstCoordinate, firstCoordObstacle);
    } else {
        return std::min(firstCoordinate, firstCoordObstacle);
    }
}

int advanceCoordinate(int coordinate, int speed, double timeDelta)
{
    return coordinate + speed * timeDelta;
}

} // namespace

MoveProcessor::MoveProcessor(const Map& map) : map_ { map }
{}

void MoveProcessor::addObject(const std::shared_ptr<MovingObject>& object)
{
    objects_.push_back(object);
}

void MoveProcessor::deleteObject(const std::shared_ptr<MovingObject>& object)
{
    objects_.erase(std::remove(objects_.begin(), objects_.end(), object));
}

void MoveProcessor::performMovement(double timeDelta)
{
    for (const auto& object : objects_) {
        if (object->movementData().speed == 0) {
            continue;
        }

        timeDelta /= 42.;
        auto  moveData    = object->movementData();
        auto& coordinates = moveData.coordinates;
        auto  oldIndex    = map_.coordinatesToIndex(coordinates);
        // const auto& newCoordinates = advanceCoordinates(coordinates, timeDelta, moveData.speed, moveData.direction);
        auto      inCell = map_.coordinatesInCell(coordinates);
        const int ds     = 5;

        // int inCellOrtogonalCoord  = inCellCoordinate(newCoordinates, moveData.direction);
        const int firstCoord            = firstCoordinate(coordinates, moveData.direction);
        const int firstCoordBestAdvance = advanceCoordinate(firstCoord, moveData.speed, timeDelta);
        const int firstCoordObstacle    = map_.firstCoordinateObstacle(coordinates, moveData.direction);
        const int maxFirstCoordAdvance =
            maxFirstCoordinateAdvance(firstCoordBestAdvance, firstCoordObstacle, moveData.direction);

        if (moveData.direction == Direction::Upward) {
            coordinates.setY(maxFirstCoordAdvance);
            auto d = abs(inCell.x() - cellHalfSize);
            if (inCell.x() > cellHalfSize) {
                auto obstacleCoords = map_.findUpwardRightObstacle(coordinates);
                if (map_.circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setX(coordinates.x() - ds);
                    } else {
                        coordinates.setX(coordinates.x() - d);
                    }
                }
            } else if (inCell.x() < cellHalfSize) {
                auto obstacleCoords = map_.findUpwardLeftObstacle(coordinates);
                if (map_.circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setX(coordinates.x() + ds);
                    } else {
                        coordinates.setX(coordinates.x() + d);
                    }
                }
            }
        } else if (moveData.direction == Direction::Right) {
            coordinates.setX(maxFirstCoordAdvance);
            auto d = abs(inCell.y() - cellHalfSize);
            if (inCell.y() > cellHalfSize) {
                auto obstacleCoords = map_.findRightBottomObstacle(coordinates);
                if (map_.circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setY(coordinates.y() - ds);
                    } else {
                        coordinates.setY(coordinates.y() - d);
                    }
                }
            } else if (inCell.x() < cellHalfSize) {
                auto obstacleCoords = map_.findRightTopObstacle(coordinates);
                if (map_.circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setY(coordinates.y() + ds);
                    } else {
                        coordinates.setY(coordinates.y() + d);
                    }
                }
            }
        } else if (moveData.direction == Direction::Downward) {
            coordinates.setY(maxFirstCoordAdvance);
            auto d = abs(inCell.x() - cellHalfSize);
            if (inCell.x() > cellHalfSize) {
                auto obstacleCoords = map_.findDownwardRightObstacle(coordinates);
                if (map_.circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setX(coordinates.x() - ds);
                    } else {
                        coordinates.setX(coordinates.x() - d);
                    }
                }
            } else if (inCell.x() < cellHalfSize) {
                auto obstacleCoords = map_.findDownwardLeftObstacle(coordinates);
                if (map_.circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setX(coordinates.x() + ds);
                    } else {
                        coordinates.setX(coordinates.x() + d);
                    }
                }
            }
        } else if (moveData.direction == Direction::Left) {
            coordinates.setX(maxFirstCoordAdvance);
            auto d = abs(inCell.y() - cellHalfSize);
            if (inCell.y() > cellHalfSize) {
                auto obstacleCoords = map_.findLeftBottomObstacle(coordinates);
                if (map_.circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setY(coordinates.y() - ds);
                    } else {
                        coordinates.setY(coordinates.y() - d);
                    }
                }
            } else if (inCell.x() < cellHalfSize) {
                auto obstacleCoords = map_.findLeftTopObstacle(coordinates);
                if (map_.circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setY(coordinates.y() + ds);
                    } else {
                        coordinates.setY(coordinates.y() + d);
                    }
                }
            }
        }

        object->setMovementData(moveData);
        auto newIndex = map_.coordinatesToIndex(coordinates);
        if (oldIndex != newIndex) {
            emit objectIndexChanged(object, newIndex);
        }

        emit characterMoved(object);
    }
}

} // namespace bm
