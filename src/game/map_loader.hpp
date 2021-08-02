#ifndef MAP_LOADER_HPP
#define MAP_LOADER_HPP

#include "map.hpp"
#include "bomberman.hpp"
#include "bot.hpp"

#include <QString>

#include <memory>

namespace bm {
namespace map_loader {

struct MapData
{
    std::shared_ptr<Map>                    map;
    std::vector<std::shared_ptr<Bomberman>> bombermans;
    std::vector<std::shared_ptr<Bot>>       bots;
};

MapData              loadFromFile(const QString& filePath);
std::unique_ptr<Map> createTestMap();

} // namespace map_loader
} // namespace bm

#endif // MAP_LOADER_HPP
