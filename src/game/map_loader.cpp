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
            map->setCellType(leftBorder, CellStructure::Concrete);
            map->setCellType(rightBorder, CellStructure::Concrete);
            map->setCellType(topBorder, CellStructure::Concrete);
            map->setCellType(bottomBorder, CellStructure::Concrete);
        }

        map->setCellType(33, CellStructure::Concrete);
        map->setCellType(35, CellStructure::Concrete);
        map->setCellType(53, CellStructure::Concrete);
        map->setCellType(55, CellStructure::Concrete);
        map->setCellType(24, CellStructure::Bricks);
        map->setCellType(42, CellStructure::Bricks);
        map->setCellType(46, CellStructure::Bricks);
        map->setCellType(64, CellStructure::Bricks);

        return map;
    } catch (...) {
        return nullptr;
    }
}
} // namespace bm
