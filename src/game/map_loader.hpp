#ifndef MAP_LOADER_HPP
#define MAP_LOADER_HPP

#include "map.hpp"

#include <QString>

#include <memory>

namespace bm {

std::unique_ptr<Map> loadFromFile(const QString& filePath);
std::unique_ptr<Map> createTestMap();

}  // namespace bm

#endif // MAP_LOADER_HPP
