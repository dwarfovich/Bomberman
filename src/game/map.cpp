#include "map.hpp"

#include <stdexcept>

namespace bm {
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
    }
    catch (const std::exception& e) {
        return (false);
    }

    width_ = width;
    height_ = height;

    return (true);
}

void Map::setCellType(size_t index, CellType type)
{
    if (isProperIndex(index)) {
        map_[index].type = type;
    }

    emit cellChanged(index);
}

bool Map::placeBomb(size_t index)
{
    if (isProperIndex(index)) {
        map_[index].hasBomb = true;
        return (true);
    }
    else {
        return (false);
    }
}

void Map::setPlayer(const std::shared_ptr<Bomberman>& player)
{
    player_ = player;
}

bool Map::moveCharacter(Character& object, Direction direction)
{
    if (canMoveCharacter(object, direction)) {
        object.location += coordinatesShift(direction);
        return (true);
    }
    else {
        return (false);
    }
}

QPoint Map::indexToCoordinates(size_t index) const
{
    if (index < map_.size()) {
        return {static_cast<int>(index % width_), static_cast<int>(index / width_)};
    }
    else {
        return {-1, -1};
    }
}

size_t Map::coordinatesToIndex(const QPoint& point) const
{
    if (point.x() < width_ && point.y() >= 0 && point.y() >= 0 && point.y() < height_) {
        return (point.y() * width_ + point.x());
    }
    else {
        return (wrongIndex);
    }
}

bool Map::canMoveCharacter(const Character& object, Direction direction) const
{
    size_t targetIndex =
        coordinatesToIndex({object.location + coordinatesShiftByDirection[directionToIndex(direction)]});

    return (targetIndex != wrongIndex && map_[targetIndex].type == CellType::Empty);
}

bool Map::isProperIndex(size_t index) const
{
    return (index < map_.size());
}

size_t Map::width() const
{
    return (width_);
}

size_t Map::height() const
{
    return (height_);
}

const std::vector<Cell>& Map::map() const
{
    return (map_);
}

const std::vector<QPoint>& Map::bombs() const
{
    return (bombs_);
}

const std::shared_ptr<Bomberman>& Map::player() const
{
    return (player_);
}
}  // namespace bm
