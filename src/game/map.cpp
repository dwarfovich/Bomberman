#include "map.hpp"
#include "map_constants.hpp"
#include "character_factory.hpp"
#include "bot_factory.hpp"
#include "bomberman.hpp"

#include <QRect>
#include <QDebug>
#define DEB qDebug()

#include <algorithm>
#include <stdexcept>

namespace bm {

namespace {

QPoint advanceCoordinates(const QPoint& coordinates, double timeDelta, int speed, Direction direction)
{
    auto newLocation = coordinates;
    if (direction == Direction::Upward || direction == Direction::Downward) {
        newLocation.setY(newLocation.y() + speed * timeDelta / 150.);
    } else {
        newLocation.setX(newLocation.x() + speed * timeDelta / 150.);
    }
    return newLocation;
}

} // namespace

QDataStream& operator<<(QDataStream& stream, const Map& map)
{
    stream << map.widthInCells_ << map.heightInCells_;
    for (const auto& cell : map.cells_) {
        stream << cell;
    }

    auto s = map.movingObjects_;
    stream << map.movingObjects_.size();
    for (const auto& object : map.movingObjects_) {
        stream << *object;
    }

    //    stream << map.bombs_.size();
    //    for (const auto& bomb : map.bombs_) {
    //        stream << *bomb;
    //    }

    //    stream << map.explosions_.size();
    //    for (const auto& explosion : map.explosions_) {
    //        stream << explosion;
    //    }

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Map& map)
{
    stream >> map.widthInCells_;
    stream >> map.heightInCells_;
    size_t cellsCount = map.widthInCells_ * map.heightInCells_;
    // TODO: Handle exception.
    map.cells_.resize(cellsCount);
    for (auto& cell : map.cells_) {
        stream >> cell;
    }

    size_t charactersCount = 0;
    stream >> charactersCount;
    for (size_t i = 0; i < charactersCount; ++i) {
        ObjectType type;
        stream >> type;
        if (type == ObjectType::Bomberman) {
            auto bomberman = std::make_shared<Bomberman>();
            stream >> *bomberman;
            map.addBomberman(bomberman);
        } else if (type == ObjectType::Bot) {
            std::shared_ptr<Bot> bot = createBot(BotType::Regular, map);
            stream >> *bot;
            map.addBot(bot);
            // map.addMovingObject(bot);
        }
    }

    //    size_t bombsCount = 0;
    //    stream >> bombsCount;
    //    for (size_t i = 0; i < bombsCount; ++i) {
    //        auto bomb = std::make_shared<Bomb>();
    //        stream >> *bomb;
    //        map.placeBomb(bomb);
    //    }

    //    // TODO: Refactor dummy read of explosions.
    //    size_t explosionsCount = 0;
    //    stream >> explosionsCount;
    //    for (size_t i = 0; i < explosionsCount; ++i) {
    //        Explosion e { {}, { 0, 0 }, { 0, 0 } };
    //        stream >> e;
    //    }

    return stream;
}

Map::Map(size_t width, size_t height)
{
    if (!reset(width, height)) {
        throw std::runtime_error("Cann't initialize map");
    }
}

bool Map::reset(size_t width, size_t height)
{
    if (width == 0 || height == 0) {
        return false;
    }

    try {
        cells_.resize(width * height);
    } catch (const std::exception&) {
        return false;
    }

    widthInCells_  = width;
    heightInCells_ = height;
    for (size_t i = 0; i < cells_.size(); ++i) {
        cells_[i].setIndex(i);
    }

    return (true);
}

void Map::setCellType(size_t index, CellStructure structure)
{
    if (isProperIndex(index)) {
        cells_[index].setStructure(structure);
    }

    emit cellChanged(index);
}

bool Map::placeBomb(const std::shared_ptr<Bomb>& bomb)
{
    if (isProperIndex(bomb->cellIndex)) {
        cells_[bomb->cellIndex].setHasBomb(true);
        bombs_.push_back(bomb);
        emit cellChanged(bomb->cellIndex);
        return true;
    } else {
        return false;
    }
}

bool Map::removeBomb(size_t index)
{
    auto iter = std::find_if(bombs_.cbegin(), bombs_.cend(), [index](const auto& bomb) {
        return bomb->cellIndex == index;
    });
    if (iter == bombs_.cend()) {
        return false;
    }
    bombs_.erase(iter);
    cells_[index].setHasBomb(false);
    emit cellChanged(index);

    return true;
}

bool Map::setModifier(size_t index, const std::shared_ptr<IModifier>& modifier)
{
    if (isProperIndex(index)) {
        cells_[index].setModifier(modifier);
        emit cellChanged(index);
        return true;
    } else {
        return false;
    }
}

void Map::addBomberman(const std::shared_ptr<Bomberman>& bomberman)
{
    bombermans_.emplace(bomberman.get(), bomberman);
    movingObjects_.push_back(bomberman);
}

void Map::removeBomberman(const Bomberman& bomberman)
{
    auto iter = bombermans_.find(&bomberman);
    if (iter != bombermans_.cend()) {
        removeMovingObject(iter->second);
        bombermans_.erase(iter);
    }
}

void Map::addBot(const std::shared_ptr<Bot>& bot)
{
    bots_.push_back(bot);
    movingObjects_.push_back(bot);
}

// void Map::addMovingObject(const std::shared_ptr<MovingObject>& object)
//{
//    movingObjects_.push_back(object);
//}

void Map::removeMovingObject(const std::shared_ptr<MovingObject>& object)
{
    // TODO: Also remove from bombermans_ and bots_.
    movingObjects_.erase(std::remove(movingObjects_.begin(), movingObjects_.end(), object));
}

const std::shared_ptr<MovingObject>& Map::sharedPtrForObject(const MovingObject& object) const
{
    const MovingObject* objectPtr = &object;
    auto iter = std::find_if(movingObjects_.cbegin(), movingObjects_.cend(), [objectPtr](const auto& pointer) {
        return (pointer.get() == objectPtr);
    });

    if (iter != movingObjects_.cend()) {
        return *iter;
    } else {
        static const std::shared_ptr<MovingObject> empty = nullptr;
        return empty;
    }
}

void Map::removeMovingObject(const MovingObject& object)
{
    const MovingObject* objectPtr = &object;
    movingObjects_.erase(std::remove_if(movingObjects_.begin(), movingObjects_.end(), [objectPtr](const auto& iter) {
        return iter.get() == objectPtr;
    }));
}

const Cell& Map::cell(size_t index) const
{
    return cells_[index];
}

CellLocation Map::coordinatesToLocation(const QPoint& coordinates) const
{
    return { static_cast<size_t>(coordinates.x() / cellSize), static_cast<size_t>(coordinates.y() / cellSize) };
}

QPoint Map::locationToCellCenterCoordinates(const CellLocation& location) const
{
    auto index = locationToIndex(location);
    return indexToCellCenterCoordinates(index);
}

size_t Map::coordinatesToIndex(const QPoint& point) const
{
    if (point.x() < widthInCells_ * cellSize && point.y() >= 0 && point.y() >= 0
        && point.y() < heightInCells_ * cellSize) {
        return ((point.y() / cellSize * widthInCells_) + point.x() / cellSize);
    } else {
        return invalidMapIndex;
    }
}

size_t Map::locationToIndex(const CellLocation& location) const
{
    return location.x() + location.y() * widthInCells_;
}

CellLocation Map::indexToLocation(size_t index) const
{
    if (index == invalidMapIndex) {
        return invalidCellLocation;
    } else {
        return { index % widthInCells_, index / widthInCells_ };
    }
}

bool Map::cellIsMovable(const CellLocation& location) const
{
    auto index = locationToIndex(location);
    if (index == invalidMapIndex) {
        return false;
    } else {
        return cells_[index].structure() == CellStructure::Empty;
    }
}

bool Map::nextCellIsMovable(const MovingObject& object, Direction direction) const
{
    return nextCellIsMovable(object.coordinates(), direction);
}

bool Map::nextCellIsMovable(const QPoint& coordinates, Direction direction) const
{
    const auto currentIndex = coordinatesToIndex(coordinates);
    const auto targetIndex  = shiftIndex(currentIndex, direction);

    return (targetIndex != invalidMapIndex && targetIndex < cells_.size()
            && cells_[targetIndex].structure() == CellStructure::Empty);
}

bool Map::isProperIndex(size_t index) const
{
    return (index != invalidMapIndex && index < cells_.size());
}

size_t Map::width() const
{
    return (widthInCells_);
}

size_t Map::height() const
{
    return (heightInCells_);
}

const std::vector<Cell>& Map::cells() const
{
    return (cells_);
}

const Map::RespawnPlaces& Map::playerRespawns() const
{
    auto iter = respawnPlaces_.find(RespawnType::Bomberman);
    if (iter != respawnPlaces_.cend()) {
        return iter->second;
    } else {
        static const RespawnPlaces empty;
        return empty;
    }
}

QPoint Map::indexToCellCenterCoordinates(size_t index) const
{
    return { static_cast<int>((index % widthInCells_) * cellSize + cellHalfSize),
             static_cast<int>((index / widthInCells_) * cellSize + cellHalfSize) };
}

bool Map::isCellCenter(const QPoint& coordinates) const
{
    return (coordinates.x() % cellSize == cellHalfSize && coordinates.y() % cellSize == cellHalfSize);
}

void Map::alignToCenter(double timeDelta, Character& character)
{
    const auto& moveData       = character.movementData();
    const auto& location       = character.movementData().coordinates;
    auto        newCoordinates = advanceCoordinates(location, timeDelta, moveData.speed, moveData.direction);
    auto        inCell         = coordinatesInCell(newCoordinates);
    if (moveData.direction == Direction::Upward) {
        if (inCell.x() > cellHalfSize + 5) {
            newCoordinates.setX(newCoordinates.x() - 5);
        } else if (inCell.x() > cellHalfSize) {
            newCoordinates.setX(newCoordinates.x() - inCell.x() + cellHalfSize);
        }
    }

    character.setCoordinates(newCoordinates);
}

CellLocation Map::upperRightLocation(const CellLocation& location) const
{
    auto nextLocation = location;
    nextLocation.incrementX();
    nextLocation.decrementY();

    return nextLocation;
}

CellLocation Map::upperLeftLocation(const CellLocation& location) const
{
    auto nextLocation = location;
    nextLocation.decrementX();
    nextLocation.decrementY();

    return nextLocation;
}

CellLocation Map::shiftLocation(const CellLocation& location, int dx, int dy) const
{
    // TODO: reimplement
    auto newLocation = location;
    if (dx < 0) {
        for (int i = 0; i < -dx; ++i) {
            newLocation.decrementX();
        }
    } else {
        for (int i = 0; i < dx; ++i) {
            newLocation.incrementX();
        }
    }

    if (dy < 0) {
        for (int i = 0; i < -dy; ++i) {
            newLocation.decrementY();
        }
    } else {
        for (int i = 0; i < dy; ++i) {
            newLocation.incrementY();
        }
    }

    return newLocation;
}

bool Map::circlesIntersect(const QPoint& center1, const QPoint& center2) const
{
    int dSquare = (center1.x() - center2.x()) * (center1.x() - center2.x())
                  + (center1.y() - center2.y()) * (center1.y() - center2.y());

    return dSquare < cellSize * cellSize;
}

int Map::moveCoordinateY(int y, int speed, int timeDelta) const
{
    return y + speed * timeDelta;
}

int Map::findXObstacle(const QPoint& coordinates, Direction direction) const
{
    if (direction == Direction::Right) {
        if (nextCellIsMovable(coordinates, direction)) {
            return widthInCells_ * cellSize;
        } else {
            return (coordinates.x() / cellSize) * cellSize + cellHalfSize;
        }
    } else if (direction == Direction::Left) {
        if (nextCellIsMovable(coordinates, direction)) {
            return 0;
        } else {
            return (coordinates.x() / cellSize) * cellSize + cellHalfSize;
        }
    }

    return 0;
}

int Map::findYObstacle(const QPoint& coordinates, Direction direction) const
{
    if (direction == Direction::Upward) {
        if (nextCellIsMovable(coordinates, direction)) {
            return 0;
        } else {
            return (coordinates.y() / cellSize) * cellSize + cellHalfSize;
        }
    } else if (direction == Direction::Downward) {
        if (nextCellIsMovable(coordinates, direction)) {
            return heightInCells_ * cellSize;
        } else {
            return (coordinates.y() / cellSize) * cellSize + cellHalfSize;
        }
    }

    return 0;
}

QPoint Map::findUpwardRightObstacle(const QPoint& coordinates) const
{
    auto location      = coordinatesToLocation(coordinates);
    auto rightLocation = shiftLocation(location, 1, 0);
    if (!cellIsMovable(rightLocation)) {
        return locationToCellCenterCoordinates(rightLocation);
    }
    auto topRightLocation = shiftLocation(location, 1, -1);
    if (!cellIsMovable(topRightLocation)) {
        return locationToCellCenterCoordinates(topRightLocation);
    }

    return invalidCoordinates;
}

QPoint Map::findUpwardLeftObstacle(const QPoint& coordinates) const
{
    auto location     = coordinatesToLocation(coordinates);
    auto leftLocation = shiftLocation(location, -1, 0);
    if (!cellIsMovable(leftLocation)) {
        return locationToCellCenterCoordinates(leftLocation);
    }
    auto topLeftLocation = shiftLocation(location, 1, -1);
    if (!cellIsMovable(topLeftLocation)) {
        return locationToCellCenterCoordinates(topLeftLocation);
    }

    return invalidCoordinates;
}

QPoint Map::findRightTopObstacle(const QPoint& coordinates) const
{
    auto location    = coordinatesToLocation(coordinates);
    auto topLocation = shiftLocation(location, 0, -1);
    if (!cellIsMovable(topLocation)) {
        return locationToCellCenterCoordinates(topLocation);
    }
    auto topTopRightLocation = shiftLocation(location, 1, -1);
    if (!cellIsMovable(topTopRightLocation)) {
        return locationToCellCenterCoordinates(topTopRightLocation);
    }

    return invalidCoordinates;
}

QPoint Map::findRightBottomObstacle(const QPoint& coordinates) const
{
    auto location       = coordinatesToLocation(coordinates);
    auto bottomLocation = shiftLocation(location, 0, 1);
    if (!cellIsMovable(bottomLocation)) {
        return locationToCellCenterCoordinates(bottomLocation);
    }
    auto rightBottomLocation = shiftLocation(location, 1, 1);
    if (!cellIsMovable(rightBottomLocation)) {
        return locationToCellCenterCoordinates(rightBottomLocation);
    }

    return invalidCoordinates;
}

QPoint Map::findDownwardRightObstacle(const QPoint& coordinates) const
{
    auto location      = coordinatesToLocation(coordinates);
    auto rightLocation = shiftLocation(location, 1, 0);
    if (!cellIsMovable(rightLocation)) {
        return locationToCellCenterCoordinates(rightLocation);
    }
    auto bottomRightLocation = shiftLocation(location, 1, 1);
    if (!cellIsMovable(bottomRightLocation)) {
        return locationToCellCenterCoordinates(bottomRightLocation);
    }

    return invalidCoordinates;
}

QPoint Map::findDownwardLeftObstacle(const QPoint& coordinates) const
{
    auto location     = coordinatesToLocation(coordinates);
    auto leftLocation = shiftLocation(location, -1, 0);
    if (!cellIsMovable(leftLocation)) {
        return locationToCellCenterCoordinates(leftLocation);
    }
    auto bottomLeftLocation = shiftLocation(location, -1, 1);
    if (!cellIsMovable(bottomLeftLocation)) {
        return locationToCellCenterCoordinates(bottomLeftLocation);
    }

    return invalidCoordinates;
}

QPoint Map::findLeftBottomObstacle(const QPoint& coordinates) const
{
    auto location       = coordinatesToLocation(coordinates);
    auto bottomLocation = shiftLocation(location, 0, 1);
    if (!cellIsMovable(bottomLocation)) {
        return locationToCellCenterCoordinates(bottomLocation);
    }
    auto topBottomRightLocation = shiftLocation(location, -1, 1);
    if (!cellIsMovable(topBottomRightLocation)) {
        return locationToCellCenterCoordinates(topBottomRightLocation);
    }

    return invalidCoordinates;
}

QPoint Map::findLeftTopObstacle(const QPoint& coordinates) const
{
    auto location    = coordinatesToLocation(coordinates);
    auto topLocation = shiftLocation(location, 0, -1);
    if (!cellIsMovable(topLocation)) {
        return locationToCellCenterCoordinates(topLocation);
    }
    auto topLeftLocation = shiftLocation(location, -1, -1);
    if (!cellIsMovable(topLeftLocation)) {
        return locationToCellCenterCoordinates(topLeftLocation);
    }

    return invalidCoordinates;
}

int Map::firstCoordinateObstacle(const QPoint& coordinates, Direction direction) const
{
    if (direction == Direction::Upward || direction == Direction::Downward) {
        return findYObstacle(coordinates, direction);
    } else {
        return findXObstacle(coordinates, direction);
    }
}

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

int Map::inCellCoordinate(const QPoint& coordinates, Direction direction)
{
    const auto& inCell = coordinatesInCell(coordinates);
    if (direction == Direction::Upward || direction == Direction::Downward) {
        return inCell.x();
    } else {
        return inCell.y();
    }
}

const std::vector<std::shared_ptr<Bot>>& Map::bots() const
{
    return bots_;
}

void Map::moveObjects(double timeDelta)
{
    timeDelta /= 42.;
    for (const auto& object : movingObjects_) {
        if (object->movementData().speed == 0) {
            continue;
        }

        auto  moveData    = object->movementData();
        auto& coordinates = moveData.coordinates;
        auto  oldIndex    = coordinatesToIndex(coordinates);
        auto  inCell      = coordinatesInCell(coordinates);
        int   ds          = 5;

        const int firstCoord            = firstCoordinate(coordinates, moveData.direction);
        const int firstCoordBestAdvance = advanceCoordinate(firstCoord, moveData.speed, timeDelta);
        const int firstCoordObstacle    = firstCoordinateObstacle(coordinates, moveData.direction);
        const int maxFirstCoordAdvance =
            maxFirstCoordinateAdvance(firstCoordBestAdvance, firstCoordObstacle, moveData.direction);

        if (moveData.direction == Direction::Upward) {
            coordinates.setY(maxFirstCoordAdvance);
            auto d = abs(inCell.x() - cellHalfSize);
            if (inCell.x() > cellHalfSize) {
                auto obstacleCoords = findUpwardRightObstacle(coordinates);
                if (circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setX(coordinates.x() - ds);
                    } else {
                        coordinates.setX(coordinates.x() - d);
                    }
                }
            } else if (inCell.x() < cellHalfSize) {
                auto obstacleCoords = findUpwardLeftObstacle(coordinates);
                if (circlesIntersect(coordinates, obstacleCoords)) {
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
                auto obstacleCoords = findRightBottomObstacle(coordinates);
                if (circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setY(coordinates.y() - ds);
                    } else {
                        coordinates.setY(coordinates.y() - d);
                    }
                }
            } else if (inCell.x() < cellHalfSize) {
                auto obstacleCoords = findRightTopObstacle(coordinates);
                if (circlesIntersect(coordinates, obstacleCoords)) {
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
                auto obstacleCoords = findDownwardRightObstacle(coordinates);
                if (circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setX(coordinates.x() - ds);
                    } else {
                        coordinates.setX(coordinates.x() - d);
                    }
                }
            } else if (inCell.x() < cellHalfSize) {
                auto obstacleCoords = findDownwardLeftObstacle(coordinates);
                if (circlesIntersect(coordinates, obstacleCoords)) {
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
                auto obstacleCoords = findLeftBottomObstacle(coordinates);
                if (circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setY(coordinates.y() - ds);
                    } else {
                        coordinates.setY(coordinates.y() - d);
                    }
                }
            } else if (inCell.x() < cellHalfSize) {
                auto obstacleCoords = findLeftTopObstacle(coordinates);
                if (circlesIntersect(coordinates, obstacleCoords)) {
                    if (d > ds) {
                        coordinates.setY(coordinates.y() + ds);
                    } else {
                        coordinates.setY(coordinates.y() + d);
                    }
                }
            }
        }

        object->setMovementData(moveData);
        auto newIndex = coordinatesToIndex(coordinates);
        if (oldIndex != newIndex) {
            emit objectIndexChanged(object, newIndex);
        }

        emit objectMoved(object);
        if (object->notifyIfMeetedWall()) {
            if (!nextCellIsMovable(*object, object->movementData().direction) && isCellCenter(object->coordinates())) {
                object->meetsWall();
            }
        }
    }

    checkCollisions();
}

const Map::RespawnPlaces& Map::respawnPlaces(RespawnType type) const
{
    auto iter = respawnPlaces_.find(type);
    if (iter != respawnPlaces_.cend()) {
        return iter->second;
    } else {
        static const RespawnPlaces empty {};
        return empty;
    }
}

void Map::setRespawnPlaces(RespawnType type, const RespawnPlaces& places)
{
    respawnPlaces_[type] = places;
}

void Map::checkCollisions()
{
    for (size_t i = 0; i < movingObjects_.size(); ++i) {
        for (size_t j = i + 1; j < movingObjects_.size(); ++j) {
            if (objectsIntersect(*movingObjects_[i], *movingObjects_[j])) {
                emit objectsCollided(*movingObjects_[i], *movingObjects_[j]);
            }
        }
    }
}

bool Map::objectsIntersect(MovingObject& lhs, MovingObject& rhs)
{
    QRect left { lhs.coordinates(), QSize { cellSize, cellSize } };
    QRect right { rhs.coordinates(), QSize { cellSize, cellSize } };

    return left.intersects(right);
}

// void Map::moveObjects(double timeDelta)
//{
//    if (player_->moveData.speed != 0) {
//        timeDelta /= 42.;
//        const auto& moveData       = player_->moveData;
//        auto&       coordinates    = player_->moveData.coordinates;
//        auto        oldIndex       = coordinatesToIndex(coordinates);
//        const auto& newCoordinates = advanceCoordinates(coordinates, timeDelta, moveData.speed, moveData.direction);
//        auto        inCell         = coordinatesInCell(newCoordinates);
//        const int ds = 5;
//        if (moveData.direction == Direction::Upward) {
//            int nextY     = coordinates.y() + moveData.speed * timeDelta;
//            int yObstacle = findYObstacle(coordinates, moveData.direction);
//            int maxY      = std::max(nextY, yObstacle);
//            coordinates.setY(maxY);
//            auto d = abs(inCell.x() - cellHalfSize);
//            if (inCell.x() > cellHalfSize) {
//                auto obstacleCoords = findRightTopObstacle(coordinates);
//                if (circlesIntersect(coordinates, obstacleCoords)) {
//                    if (d > ds) {
//                        coordinates.setX(coordinates.x() - ds);
//                    } else {
//                        coordinates.setX(coordinates.x() - d);
//                    }
//                }
//            } else if (inCell.x() < cellHalfSize) {
//                auto obstacleCoords = findLeftTopObstacle(coordinates);
//                if (circlesIntersect(coordinates, obstacleCoords)) {
//                    if (d > ds) {
//                        coordinates.setX(coordinates.x() + ds);
//                    } else {
//                        coordinates.setX(coordinates.x() + d);
//                    }
//                    // coordinates.setX(coordinates.x() + ds);
//                }
//            }
//        } else if (moveData.direction == Direction::Right) {
//            int nextX     = coordinates.x() + moveData.speed * timeDelta;
//            int xObstacle = findXObstacle(coordinates, moveData.direction);
//            coordinates.setX(std::min(nextX, xObstacle));
//            auto d = abs(inCell.x() - cellHalfSize);
//            if (inCell.y() > cellHalfSize) {
//                auto obstacleCoords = findBottomObstacle(coordinates);
//                if (circlesIntersect(coordinates, obstacleCoords)) {
//                    if (d > ds) {
//                        coordinates.setY(coordinates.y() - ds);
//                    } else {
//                        coordinates.setY(coordinates.y() - d);
//                    }
//                    // coordinates.setY(coordinates.y() - ds);
//                }
//            } else if (inCell.x() < cellHalfSize) {
//                auto obstacleCoords = findTopObstacle(coordinates);
//                if (circlesIntersect(coordinates, obstacleCoords)) {
//                    if (d > ds) {
//                        coordinates.setY(coordinates.y() + ds);
//                    } else {
//                        coordinates.setY(coordinates.y() + d);
//                    }
//                    // coordinates.setY(coordinates.y() + ds);
//                }
//            }
//        } else if (moveData.direction == Direction::Downward) {
//            int nextY     = coordinates.y() + moveData.speed * timeDelta;
//            int yObstacle = findYObstacle(coordinates, moveData.direction);
//            coordinates.setY(std::min(nextY, yObstacle));
//            auto d = abs(inCell.x() - cellHalfSize);
//            if (inCell.x() > cellHalfSize) {
//                auto obstacleCoords = findDownwardRightObstacle(coordinates);
//                if (circlesIntersect(coordinates, obstacleCoords)) {
//                    if (d > ds) {
//                        coordinates.setX(coordinates.x() - ds);
//                    } else {
//                        coordinates.setX(coordinates.x() - d);
//                    }
//                    // coordinates.setX(coordinates.x() - ds);
//                }
//            } else if (inCell.x() < cellHalfSize) {
//                auto obstacleCoords = findDownwardLeftObstacle(coordinates);
//                if (circlesIntersect(coordinates, obstacleCoords)) {
//                    if (d > ds) {
//                        coordinates.setX(coordinates.x() + ds);
//                    } else {
//                        coordinates.setX(coordinates.x() + d);
//                    }
//                    // coordinates.setX(coordinates.x() + ds);
//                }
//            }
//        } else if (moveData.direction == Direction::Left) {
//            int nextX     = coordinates.x() + moveData.speed * timeDelta;
//            int xObstacle = findXObstacle(coordinates, moveData.direction);
//            coordinates.setX(std::max(nextX, xObstacle));
//            auto d = abs(inCell.x() - cellHalfSize);
//            if (inCell.y() > cellHalfSize) {
//                auto obstacleCoords = findLeftBottomObstacle(coordinates);
//                if (circlesIntersect(coordinates, obstacleCoords)) {
//                    if (d > ds) {
//                        coordinates.setY(coordinates.y() - ds);
//                    } else {
//                        coordinates.setY(coordinates.y() - d);
//                    }
//                    // coordinates.setY(coordinates.y() - ds);
//                }
//            } else if (inCell.x() < cellHalfSize) {
//                auto obstacleCoords = findLeftwardTopObstacle(coordinates);
//                if (circlesIntersect(coordinates, obstacleCoords)) {
//                    if (d > ds) {
//                        coordinates.setY(coordinates.y() + ds);
//                    } else {
//                        coordinates.setY(coordinates.y() + d);
//                    }
//                    // coordinates.setY(coordinates.y() + ds);
//                }
//            }
//        }

//        auto newIndex = coordinatesToIndex(coordinates);
//        if (oldIndex != newIndex) {
//            emit bombermanIndexChanged(player_, newIndex);
//        }

//        emit characterMoved(player_);
//    }
//}

size_t Map::shiftIndex(size_t index, Direction direction) const
{
    QPoint location = { static_cast<int>(index % widthInCells_), static_cast<int>(index / widthInCells_) };
    location += coordinatesShift(direction);

    return location.x() + location.y() * widthInCells_;
}

int Map::alignToCellCenter(int position) const
{
    return (position / cellSize) * cellSize + cellHalfSize;
}

void Map::addGameObjectsForCell(const CellLocation& location, std::vector<GameObject*>& objects)
{
    auto index = locationToIndex(location);
    addGameObjectsForCell(index, objects);
}

void Map::addGameObjectsForCell(size_t index, std::vector<GameObject*>& objects)
{
    objects.push_back(&cells_[index]);
    for (const auto& object : movingObjects_) {
        if (coordinatesToIndex(object->movementData().coordinates) == index) {
            objects.push_back(object.get());
        }
    }
}

QPoint Map::coordinatesInCell(const QPoint& coordinates) const
{
    return { coordinates.x() - (coordinates.x() / cellSize) * cellSize,
             coordinates.y() - (coordinates.y() / cellSize) * cellSize };
}

} // namespace bm

// QPoint Map::findRightTopObstacle(const QPoint& coordinates) const
//{
//    std::vector<QPoint> v;
//    auto                location = coordinatesToLocation(coordinates);
//    auto rightLocation = shiftLocation(location, 1, 0);
//    if (!cellIsMovable(rightLocation)) {
//        v.push_back(locationToCellCenterCoordinates(rightLocation));
//        return locationToCellCenterCoordinates(rightLocation);
//    }
//    auto topRightLocation = shiftLocation(location, 1, -1);
//    if (!cellIsMovable(topRightLocation)) {
//        v.push_back(locationToCellCenterCoordinates(topRightLocation));
//        return locationToCellCenterCoordinates(topRightLocation);
//    }
//    auto topLocation = shiftLocation(location, 0, -1);
//    if (!cellIsMovable(topLocation)) {
//        v.push_back(locationToCellCenterCoordinates(topLocation));
//    }

//    auto iter = std::min_element(v.cbegin(), v.cend(), [](const QPoint& p1, const QPoint& p2) {
//        return p1.x() < p2.x();
//    });

//    if (iter != v.cend()) {
//        return *iter;
//    } else {
//        return { -1, -1 };
//    }
//}

// QPoint Map::findLeftTopObstacle(const QPoint& coordinates) const
//{
//    std::vector<QPoint> v;
//    auto                location     = coordinatesToLocation(coordinates);
//    auto                leftLocation = shiftLocation(location, -1, 0);
//    if (!cellIsMovable(leftLocation)) {
//        v.push_back(locationToCellCenterCoordinates(leftLocation));
//        return locationToCellCenterCoordinates(leftLocation);
//    }
//    auto topLeftLocation = shiftLocation(location, 1, -1);
//    if (!cellIsMovable(topLeftLocation)) {
//        v.push_back(locationToCellCenterCoordinates(topLeftLocation));
//    }
//    auto topLocation = shiftLocation(location, 0, -1);
//    if (!cellIsMovable(topLocation)) {
//        v.push_back(locationToCellCenterCoordinates(topLocation));
//    }

//    auto iter = std::min_element(v.cbegin(), v.cend(), [](const QPoint& p1, const QPoint& p2) {
//        return p1.x() < p2.x();
//    });

//    if (iter != v.cend()) {
//        return *iter;
//    } else {
//        return { -1, -1 };
//    }
//}

// QPoint Map::findTopObstacle(const QPoint& coordinates) const
//{
//    std::vector<QPoint> v;
//    auto                location = coordinatesToLocation(coordinates);

//    auto topLocation = shiftLocation(location, 0, -1);
//    if (!cellIsMovable(topLocation)) {
//        return locationToCellCenterCoordinates(topLocation);
//    }
//    auto topTopRightLocation = shiftLocation(location, 1, -1);
//    if (!cellIsMovable(topTopRightLocation)) {
//        v.push_back(locationToCellCenterCoordinates(topTopRightLocation));
//    }
//    auto bottomLocation = shiftLocation(location, 0, 1);
//    if (!cellIsMovable(bottomLocation)) {
//        v.push_back(locationToCellCenterCoordinates(bottomLocation));
//    }

//    auto iter = std::min_element(v.cbegin(), v.cend(), [](const QPoint& p1, const QPoint& p2) {
//        return p1.y() < p2.y();
//    });

//    if (iter != v.cend()) {
//        return *iter;
//    } else {
//        return { -1, -1 };
//    }
//}

// QPoint Map::findBottomObstacle(const QPoint& coordinates) const
//{
//    std::vector<QPoint> v;
//    auto                location = coordinatesToLocation(coordinates);

//    auto bottomLocation = shiftLocation(location, 0, 1);
//    if (!cellIsMovable(bottomLocation)) {
//        return locationToCellCenterCoordinates(bottomLocation);
//    }
//    auto topBottomRightLocation = shiftLocation(location, 1, 1);
//    if (!cellIsMovable(topBottomRightLocation)) {
//        v.push_back(locationToCellCenterCoordinates(topBottomRightLocation));
//    }

//    auto iter = std::min_element(v.cbegin(), v.cend(), [](const QPoint& p1, const QPoint& p2) {
//        return p1.x() < p2.x();
//    });

//    if (iter != v.cend()) {
//        return *iter;
//    } else {
//        return { -1, -1 };
//    }
//}

// QPoint Map::findDownwardRightObstacle(const QPoint& coordinates) const
//{
//    std::vector<QPoint> v;
//    auto                location = coordinatesToLocation(coordinates);

//    auto rightLocation = shiftLocation(location, 1, 0);
//    if (!cellIsMovable(rightLocation)) {
//        v.push_back(locationToCellCenterCoordinates(rightLocation));
//        return locationToCellCenterCoordinates(rightLocation);
//    }
//    auto bottomRightLocation = shiftLocation(location, 1, 1);
//    if (!cellIsMovable(bottomRightLocation)) {
//        v.push_back(locationToCellCenterCoordinates(bottomRightLocation));
//        return locationToCellCenterCoordinates(bottomRightLocation);
//    }
//    auto bottomLocation = shiftLocation(location, 0, 1);
//    if (!cellIsMovable(bottomLocation)) {
//        v.push_back(locationToCellCenterCoordinates(bottomLocation));
//    }

//    auto iter = std::min_element(v.cbegin(), v.cend(), [](const QPoint& p1, const QPoint& p2) {
//        return p1.x() < p2.x();
//    });

//    if (iter != v.cend()) {
//        return *iter;
//    } else {
//        return { -1, -1 };
//    }
//}

// QPoint Map::findDownwardLeftObstacle(const QPoint& coordinates) const
//{
//    std::vector<QPoint> v;
//    auto                location = coordinatesToLocation(coordinates);

//    auto leftLocation = shiftLocation(location, -1, 0);
//    if (!cellIsMovable(leftLocation)) {
//        v.push_back(locationToCellCenterCoordinates(leftLocation));
//        return locationToCellCenterCoordinates(leftLocation);
//    }
//    auto bottomLeftLocation = shiftLocation(location, -1, 1);
//    if (!cellIsMovable(bottomLeftLocation)) {
//        v.push_back(locationToCellCenterCoordinates(bottomLeftLocation));
//        return locationToCellCenterCoordinates(bottomLeftLocation);
//    }
//    auto bottomLocation = shiftLocation(location, 0, 1);
//    if (!cellIsMovable(bottomLocation)) {
//        v.push_back(locationToCellCenterCoordinates(bottomLocation));
//    }

//    auto iter = std::min_element(v.cbegin(), v.cend(), [](const QPoint& p1, const QPoint& p2) {
//        return p1.x() < p2.x();
//    });

//    if (iter != v.cend()) {
//        return *iter;
//    } else {
//        return { -1, -1 };
//    }
//}

// QPoint Map::findLeftBottomObstacle(const QPoint& coordinates) const
//{
//    std::vector<QPoint> v;
//    auto                location = coordinatesToLocation(coordinates);

//    auto bottomLocation = shiftLocation(location, 0, 1);
//    if (!cellIsMovable(bottomLocation)) {
//        return locationToCellCenterCoordinates(bottomLocation);
//    }
//    auto topBottomRightLocation = shiftLocation(location, -1, 1);
//    if (!cellIsMovable(topBottomRightLocation)) {
//        v.push_back(locationToCellCenterCoordinates(topBottomRightLocation));
//    }

//    auto iter = std::min_element(v.cbegin(), v.cend(), [](const QPoint& p1, const QPoint& p2) {
//        return p1.x() < p2.x();
//    });

//    if (iter != v.cend()) {
//        return *iter;
//    } else {
//        return { -1, -1 };
//    }
//}

// QPoint Map::findLeftwardTopObstacle(const QPoint& coordinates) const
//{
//    std::vector<QPoint> v;
//    auto                location = coordinatesToLocation(coordinates);

//    auto topLocation = shiftLocation(location, 0, -1);
//    if (!cellIsMovable(topLocation)) {
//        return locationToCellCenterCoordinates(topLocation);
//    }
//    auto topLeftLocation = shiftLocation(location, -1, -1);
//    if (!cellIsMovable(topLeftLocation)) {
//        v.push_back(locationToCellCenterCoordinates(topLeftLocation));
//    }

//    auto iter = std::min_element(v.cbegin(), v.cend(), [](const QPoint& p1, const QPoint& p2) {
//        return p1.x() < p2.x();
//    });

//    if (iter != v.cend()) {
//        return *iter;
//    } else {
//        return { -1, -1 };
//    }
//}
