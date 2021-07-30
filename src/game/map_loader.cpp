#include "map_loader.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

        map->setRespawnPlaces(RespawnType::Bot, {11, 18});

        return map;
    } catch (...) {
        return nullptr;
    }
}

std::unique_ptr<Map> map_loader::loadFromFile(const QString &filePath)
{
    qDebug() << filePath;
    QFile  file {filePath};
    if (!file.open(QIODevice::ReadOnly)) {
        return nullptr;
    }

    auto jsonData = file.readAll();
    QJsonParseError error;
    auto document = QJsonDocument::fromJson(jsonData, & error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing json:" << error.errorString();
        return nullptr;
    }

    const auto& jsonObject = document.object();
    size_t width = jsonObject["width"].toInt(0);
    size_t height = jsonObject["height"].toInt(0);
    if (width == 0 || height == 0) {
        return nullptr;
    }

    auto map = std::make_shared<Map>(width, height);
    const auto& mapJsonArray = jsonObject["map"].toArray();
    if (mapJsonArray.size() != width * height) {
        return nullptr;
    }

    for (int i = 0; i < mapJsonArray.size(); ++i) {
        const auto& cellObject = mapJsonArray[i].toObject();

    }

    qDebug() << width << height;

    return nullptr;
}

} // namespace bm
