#include "map_loader.hpp"

namespace bm {
std::unique_ptr<Map> loadFromFile(const QString& filePath)
{
    return nullptr;
}

std::unique_ptr<Map> createTestMap()
{
    try {
        const size_t side = 10;
        auto         map  = std::make_unique<Map>(side, side);
        for (size_t i = 0; i < side; ++i) {
            size_t leftBorder   = i * side;
            size_t rightBorder  = i * side + side - 1;
            size_t topBorder    = i;
            size_t bottomBorder = side * (side - 1) + i;
            map->setCellType(leftBorder, CellType::Concrete);
            map->setCellType(rightBorder, CellType::Concrete);
            map->setCellType(topBorder, CellType::Concrete);
            map->setCellType(bottomBorder, CellType::Concrete);
        }

        map->setCellType(33, CellType::Concrete);
        map->setCellType(35, CellType::Concrete);
        map->setCellType(53, CellType::Concrete);
        map->setCellType(55, CellType::Concrete);
        map->setCellType(24, CellType::Bricks);
        map->setCellType(42, CellType::Bricks);
        map->setCellType(46, CellType::Bricks);
        map->setCellType(64, CellType::Bricks);

        return map;
    } catch (...) {
        return nullptr;
    }
}
} // namespace bm
