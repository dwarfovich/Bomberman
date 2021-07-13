#include "map.hpp"

#include <QDebug>

#include <stdexcept>

namespace bm {

namespace {

QPoint moveLocation(const QPoint& location, double timeDelta, int speed, Direction direction)
{
    auto newLocation = location;
    if (direction == Direction::Upward || direction == Direction::Downward) {
        newLocation.setY(newLocation.y() + speed * timeDelta / 150.);
    } else {
        newLocation.setX(newLocation.x() + speed * timeDelta / 150.);
    }
    return newLocation;
}

} // namespace

Map::Map(size_t width, size_t height)
{
    if (!reset(width, height)) {
        throw std::runtime_error("Cann't initialize map");
    }
}

bool Map::reset(size_t width, size_t height)
{
    if (width == 0 || height == 0) {
        return (false);
    }

    try {
        map_.resize(width * height);
    } catch (const std::exception& e) {
        return (false);
    }

    widthInCells_  = width;
    heightInCells_ = height;

    return (true);
}

void Map::setCellType(size_t index, CellType type)
{
    if (isProperIndex(index)) {
        map_[index].type = type;
    }

    emit cellChanged(index);
}

bool Map::placeBomb(const std::shared_ptr<Bomb>& bomb)
{
    if (isProperIndex(bomb->cellIndex)) {
        map_[bomb->cellIndex].hasBomb = true;
        bombs_.push_back(bomb);
        emit cellChanged(bomb->cellIndex);
        return true;
    } else {
        return false;
    }
}

void Map::setPlayer(const std::shared_ptr<Bomberman>& player)
{
    player_ = player;
}

bool Map::moveCharacter(const std::shared_ptr<Character>& character, Direction direction)
{
    character->moveData.speed     = defaultBombermanSpeed;
    character->moveData.direction = direction;
    if (direction == Direction::Left || direction == Direction::Upward) {
        if (character->moveData.speed > 0) {
            character->moveData.speed *= -1;
        }
    } else {
        // character->moveData.speed = abs(character->moveData.speed);
    }
    // character->
    // character->location += coordinatesShift(direction);
    // emit characterMoved(character);
    return true;
}

void Map::stopCharacter(const std::shared_ptr<Character>& character, Direction direction)
{
    if (character->moveData.direction == direction) {
        character->moveData.speed = 0;
    }
}

void Map::explodeBomb(const std::shared_ptr<Bomb> &bomb)
{
    bombs_.erase(std::remove(bombs_.begin(), bombs_.end(), bomb));
    const auto& index = bomb->cellIndex;
        map_[index].hasBomb = false;
        emit cellChanged(index);
}

QPoint Map::indexToCoordinates(size_t index) const
{
    if (index < map_.size()) {
        return { static_cast<int>(index % widthInCells_), static_cast<int>(index / widthInCells_) };
    } else {
        return { -1, -1 };
    }
}

size_t Map::coordinatesToIndex(const QPoint& point) const
{
    if (point.x() < widthInCells_ * cellSize_ && point.y() >= 0 && point.y() >= 0
        && point.y() < heightInCells_ * cellSize_) {
        return ((point.y() / cellSize_ * widthInCells_) + point.x() / cellSize_);
    } else {
        return wrongIndex;
    }
}

bool Map::nextCellIsMovable(const Character& object, Direction direction) const
{
    return nextCellIsMovable(object.moveData.location, direction);
}

bool Map::nextCellIsMovable(const QPoint& location, Direction direction) const
{
    const auto currentIndex = coordinatesToIndex(location);
    const auto targetIndex  = shiftIndex(currentIndex, direction);

    return (targetIndex != wrongIndex && targetIndex < map_.size() && map_[targetIndex].type == CellType::Empty);
}

bool Map::isProperIndex(size_t index) const
{
    return (index < map_.size());
}

size_t Map::width() const
{
    return (widthInCells_);
}

size_t Map::height() const
{
    return (heightInCells_);
}

const std::vector<Cell>& Map::map() const
{
    return (map_);
}

QPoint Map::cellIndexToCenterLocation(size_t index) const
{
    return { static_cast<int>((index % widthInCells_) * cellSize_ + cellSize_ / 2),
             static_cast<int>((index / widthInCells_) * cellSize_ + cellSize_ / 2) };
}

const std::shared_ptr<Bomberman>& Map::player() const
{
    return (player_);
}

const std::vector<std::shared_ptr<Bomberman>>& Map::bombermans() const
{
    return bombermans_;
}

const std::vector<std::shared_ptr<Enemy>>& Map::enemies() const
{
    return enemies_;
}

void Map::moveObjects(double timeDelta)
{
    if (player_->moveData.speed != 0) {
        const auto& moveData    = player_->moveData;
        auto&       location    = player_->moveData.location;
        const auto& newLocation = moveLocation(location, timeDelta, moveData.speed, moveData.direction);
        if (nextCellIsMovable(*player_, moveData.direction)) {
            location = newLocation;
        } else {
            if (moveData.direction == Direction::Upward) {
                location.setY(std::max(alignToCellCenter(location.y()), newLocation.y()));
            } else if (moveData.direction == Direction::Right) {
                location.setX(std::min(alignToCellCenter(location.x()), newLocation.x()));
            } else if (moveData.direction == Direction::Downward) {
                location.setY(std::min(alignToCellCenter(location.y()), newLocation.y()));
            } else if (moveData.direction == Direction::Left) {
                location.setX(std::max(alignToCellCenter(location.x()), newLocation.x()));
            }
        }

        emit characterMoved(player_);
    }
}

size_t Map::cellSize() const
{
    return cellSize_;
}

size_t Map::shiftIndex(size_t index, Direction direction) const
{
    QPoint location = { static_cast<int>(index % widthInCells_), static_cast<int>(index / widthInCells_) };
    location += coordinatesShift(direction);

    return location.x() + location.y() * widthInCells_;
}

int Map::alignToCellCenter(int position) const
{
    return (position / cellSize_) * cellSize_ + cellSize_ / 2;
}

} // namespace bm
