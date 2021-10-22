#include "map.hpp"
#include "map_constants.hpp"
#include "character_factory.hpp"
#include "bot_factory.hpp"
#include "bomberman.hpp"

#include <QDateTime>
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
    stream << map.randomSeed_;

    stream << map.widthInCells_ << map.heightInCells_;
    for (const auto& cell : map.cells_) {
        stream << *cell;
    }

    stream << map.idToCharacterMap_.size();
    for (const auto& [id, character] : map.idToCharacterMap_) {
        stream << *character;
    }

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Map& map)
{
    stream >> map.randomSeed_;

    stream >> map.widthInCells_;
    stream >> map.heightInCells_;
    size_t cellsCount = map.widthInCells_ * map.heightInCells_;
    // TODO: Handle exception.
    map.cells_.resize(cellsCount);
    for (auto& cell : map.cells_) {
        cell = std::make_shared<Cell>();
        stream >> *cell;
    }

    size_t charactersCount = 0;
    stream >> charactersCount;
    for (size_t i = 0; i < charactersCount; ++i) {
        CharacterType type;
        stream >> type;
        if (type == CharacterType::Bomberman) {
            auto bomberman = std::make_shared<Bomberman>();
            stream >> *bomberman;
            map.addBomberman(bomberman);
        } else if (type == CharacterType::Bot) {
            std::shared_ptr<Bot> bot = createBot(BotType::Regular, map);
            stream >> *bot;
            map.addBot(bot);
        }
    }

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
        for (auto& cell : cells_) {
            cell = std::make_shared<Cell>();
        }
    } catch (const std::exception&) {
        return false;
    }

    widthInCells_  = width;
    heightInCells_ = height;
    for (size_t i = 0; i < cells_.size(); ++i) {
        cells_[i]->setIndex(i);
    }

    return true;
}

void Map::setCellType(size_t index, CellStructure structure)
{
    if (isProperIndex(index)) {
        auto previousStructure = cells_[index]->structure();
        cells_[index]->setStructure(structure);
        emit cellStructureChanged(index, previousStructure);
    }
}

void Map::setCell(const Cell& cell)
{
    auto previousCell      = cells_[cell.index()];
    auto previousStructure = cells_[cell.index()]->structure();
    if (previousCell->modifier()) {
        emit modifierRemoved(cell.index(), previousCell->modifier());
    }
    *cells_[cell.index()] = cell;
    if (cell.modifier()) {
        emit modifierAdded(cell.index(), cell.modifier());
    }
    if (previousStructure != cell.structure()) {
        emit cellStructureChanged(cell.index(), previousStructure);
    }
}

bool Map::placeBomb(const std::shared_ptr<Bomb>& bomb)
{
    // TODO: Check if cell already has a bomb.
    if (isProperIndex(bomb->cellIndex)) {
        cells_[bomb->cellIndex]->setHasBomb(true);
        bombs_.push_back(bomb);
        return true;
    } else {
        return false;
    }
}

const std::shared_ptr<Bomb> Map::removeBomb(size_t index)
{
    auto iter = std::find_if(bombs_.cbegin(), bombs_.cend(), [index](const auto& bomb) {
        return bomb->cellIndex == index;
    });
    if (iter != bombs_.cend()) {
        auto bomb = *iter;
        bombs_.erase(iter);
        cells_[index]->setHasBomb(false);
        return bomb;
    } else {
        return nullptr;
    }
}

bool Map::setModifier(size_t index, const std::shared_ptr<IModifier>& modifier)
{
    if (isProperIndex(index)) {
        auto previousModifier = cells_[index]->modifier();
        cells_[index]->setModifier(modifier);
        if (previousModifier) {
            emit modifierRemoved(index, previousModifier);
        }
        if (modifier) {
            emit modifierAdded(index, modifier);
        }
        return true;
    } else {
        return false;
    }
}

void Map::addBomberman(const std::shared_ptr<Bomberman>& bomberman)
{
    bombermans_.emplace(bomberman.get(), bomberman);
    idToCharacterMap_.emplace(bomberman->id(), bomberman);
}

void Map::removeBomberman(const Bomberman& bomberman)
{
    auto iter = idToCharacterMap_.find(bomberman.id());
    if (iter != idToCharacterMap_.cend()) {
        emit characterDestroyed(iter->second);
        bombermans_.erase(&bomberman);
        idToCharacterMap_.erase(iter);
    }
}

const std::shared_ptr<Bomberman>& Map::bomberman(object_id_t id) const
{
    auto iter = std::find_if(bombermans_.cbegin(), bombermans_.cend(), [id](const auto& iter) {
        return iter.first->id() == id;
    });
    if (iter != bombermans_.cend()) {
        return iter->second;
    } else {
        static const std::shared_ptr<Bomberman> empty;
        return empty;
    }
}

void Map::addBot(const std::shared_ptr<Bot>& bot)
{
    bots_.push_back(bot);
    idToCharacterMap_.emplace(bot->id(), bot);
}

void Map::removeBot(const std::shared_ptr<Bot>& bot)
{
    auto iter = idToCharacterMap_.find(bot->id());
    if (iter != idToCharacterMap_.cend()) {
        emit characterDestroyed(bot);
        idToCharacterMap_.erase(iter);
        bots_.erase(std::remove(bots_.begin(), bots_.end(), bot));
    }
}

void Map::moveCharacter(object_id_t id, const MoveData& moveData)
{
    auto iter = idToCharacterMap_.find(id);
    if (iter != idToCharacterMap_.cend()) {
        iter->second->setMovementData(moveData);
        emit characterMoved(iter->second);
    }
}

void Map::removeCharacter(object_id_t id)
{
    const auto& characterPtr = character(id);
    if (characterPtr) {
        emit characterDestroyed(characterPtr);
        if (characterPtr->type() == CharacterType::Bomberman) {
            const auto* bomberman = static_cast<Bomberman*>(characterPtr.get());
            bombermans_.erase(bomberman);
        } else {
            bots_.erase(std::remove(bots_.begin(), bots_.end(), characterPtr));
            // emit botRemoved();
        }
        idToCharacterMap_.erase(id);
    }
}

void Map::addExplosion(const std::shared_ptr<Explosion>& explosion)
{
    explosions_.push_back(explosion);
}

void Map::removeExplosion(object_id_t id)
{
    // TODO: Check all erase calls for proper form - you should use form with 2 arguments, where second argument is
    // end() typically.
    explosions_.erase(std::remove_if(explosions_.begin(),
                                     explosions_.end(),
                                     [this, id](std::shared_ptr<Explosion> explosion) {
                                         if (explosion->id() == id) {
                                             emit explosionRemoved(explosion);
                                             return true;
                                         } else {
                                             return false;
                                         }
                                     }),
                      explosions_.end());
}

const std::shared_ptr<Character>& Map::character(object_id_t id) const
{
    auto iter = idToCharacterMap_.find(id);
    if (iter != idToCharacterMap_.cend()) {
        return iter->second;
    } else {
        static const std::shared_ptr<Character> empty;
        return empty;
    }
}

void Map::activateExit()
{
    isExitActivated_ = true;
    emit exitActivated();
}

const Cell& Map::cell(size_t index) const
{
    return *cells_[index];
}

CellLocation Map::coordinatesToLocation(const QPoint& coordinates) const
{
    return { static_cast<size_t>(coordinates.x() / cellSize), static_cast<size_t>(coordinates.y() / cellSize) };
}

QPoint Map::indexToCoordinates(size_t index) const
{
    const auto& location = indexToLocation(index);
    return { static_cast<int>(location.x() * cellSize), static_cast<int>(location.y() * cellSize) };
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
        return cells_[index]->structure() == CellStructure::Empty;
    }
}

bool Map::nextCellIsMovable(const Character& character, Direction direction) const
{
    return nextCellIsMovable(character.coordinates(), direction);
}

bool Map::nextCellIsMovable(const QPoint& coordinates, Direction direction) const
{
    const auto currentIndex = coordinatesToIndex(coordinates);
    const auto targetIndex  = shiftIndex(currentIndex, direction);

    return (targetIndex != invalidMapIndex && targetIndex < cells_.size()
            && cells_[targetIndex]->structure() == CellStructure::Empty);
}

bool Map::isProperIndex(size_t index) const
{
    return (index != invalidMapIndex && index < cells_.size());
}

size_t Map::width() const
{
    return widthInCells_;
}

size_t Map::height() const
{
    return heightInCells_;
}

const std::vector<std::shared_ptr<Cell>>& Map::cells() const
{
    return cells_;
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
    auto        inCell         = topLeftCoordinates(newCoordinates);
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

bool Map::rectsIntersect(const QPoint& center1, const QPoint& center2) const
{
    return (abs(center1.x() - center2.x()) <= cellSize && abs(center1.y() - center2.y()) <= cellSize);
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
    const auto& inCell = topLeftCoordinates(coordinates);
    if (direction == Direction::Upward || direction == Direction::Downward) {
        return inCell.x();
    } else {
        return inCell.y();
    }
}

bool Map::isExitActivated() const
{
    return isExitActivated_;
}

size_t Map::exitIndex() const
{
    return exitCell_;
}

void Map::setExitIndex(size_t newExitCell)
{
    exitCell_ = newExitCell;
}

const QString& Map::name() const
{
    return name_;
}

void Map::setName(const QString& newName)
{
    name_ = newName;
}

uint32_t Map::randomSeed() const
{
    return randomSeed_;
}

const std::vector<std::shared_ptr<Bot>>& Map::bots() const
{
    return bots_;
}

void Map::moveObjects(double timeDelta)
{
    timeDelta /= 42.;
    for (const auto& [id, character] : idToCharacterMap_) {
        if (character->movementData().speed == 0) {
            continue;
        }

        auto  moveData    = character->movementData();
        auto& coordinates = moveData.coordinates;
        auto  oldIndex    = coordinatesToIndex(coordinates);
        auto  inCell      = topLeftCoordinates(coordinates);
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

        character->setMovementData(moveData);
        auto newIndex = coordinatesToIndex(coordinates);
        if (oldIndex != newIndex) {
            emit characterIndexChanged(character, newIndex);
        }

        emit characterMoved(character);
        if (character->notifyIfMeetedWall()) {
            if (!nextCellIsMovable(*character, character->movementData().direction)
                && isCellCenter(character->coordinates())) {
                character->meetsWall();
            }
        }
    }

    Collisions collisions;
    checkBombermanAndBotCollisions(collisions);
    checkExplosionCollisions(collisions);
    if (!collisions.empty()) {
        emit objectsCollided(collisions);
    }
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

void Map::checkBombermanAndBotCollisions(Map::Collisions& collisions)
{
    for (const auto& [bomberman, bombermanSptr] : bombermans_) {
        for (auto& bot : bots_) {
            if (charactersIntersect(*bomberman, *bot)) {
                collisions.emplace_back(bombermanSptr, bot);
            }
        }
    }
}

void Map::checkExplosionCollisions(Map::Collisions& collisions)
{
    CellLocation location;
    for (const auto& explosion : explosions_) {
        location.setY(explosion->center().y());
        for (size_t x = explosion->xMin(); x <= explosion->xMax(); ++x) {
            location.setX(x);
            addExplosionCollisionsAtLocation(location, explosion, collisions);
        }
        location.setX(explosion->center().x());
        for (size_t y = explosion->yMin(); y < explosion->center().y(); ++y) {
            location.setY(y);
            addExplosionCollisionsAtLocation(location, explosion, collisions);
        }
        for (size_t y = explosion->center().y() + 1; y <= explosion->yMax(); ++y) {
            location.setY(y);
            addExplosionCollisionsAtLocation(location, explosion, collisions);
        }
    }
}

bool Map::charactersIntersect(const Character& lhs, const Character& rhs) const
{
    return rectsIntersect(lhs.coordinates(), rhs.coordinates());
}

void Map::addExplosionCollisionsAtLocation(const CellLocation&               location,
                                           const std::shared_ptr<Explosion>& explosion,
                                           Collisions&                       collisions)
{
    size_t index = locationToIndex(location);
    collisions.emplace_back(explosion, cells_[index]);
    const auto& cellCenterCoordinates = locationToCellCenterCoordinates(location);
    for (const auto& [id, character] : idToCharacterMap_) {
        if (rectsIntersect(cellCenterCoordinates, character->coordinates())) {
            collisions.emplace_back(explosion, character);
        }
    }
}

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

void Map::addGameObjectsForCell(size_t index, std::vector<GameObject*>& objects)
{
    objects.push_back(cells_[index].get());
    for (const auto& [id, character] : idToCharacterMap_) {
        if (coordinatesToIndex(character->coordinates()) == index) {
            objects.push_back(character.get());
        }
    }
}

QPoint Map::topLeftCoordinates(const QPoint& coordinates) const
{
    return { coordinates.x() - (coordinates.x() / cellSize) * cellSize,
             coordinates.y() - (coordinates.y() / cellSize) * cellSize };
}

} // namespace bm
