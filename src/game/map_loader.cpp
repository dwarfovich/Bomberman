#include "map_loader.hpp"
#include "cell_structure.hpp"
#include "bot_factory.hpp"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <stdexcept>

namespace bm {
namespace map_loader {

namespace {
CellStructure jsonValueToCellStructure(int value)
{
    if (value >= 0 && value < static_cast<int>(CellStructure::EndValue)) {
        return static_cast<CellStructure>(value);
    } else {
        throw std::invalid_argument({});
    }
}

void parseRespawnLocations(const QJsonObject& json, MapData& mapData)
{
    const auto& array = json["player_respawns"].toArray();
    for (size_t i = 0; i < array.size(); ++i) {
        auto index     = array[i].toInt();
        auto bomberman = std::make_shared<Bomberman>();
        bomberman->setCoordinates(mapData.map->indexToCellCenterCoordinates(index));
        mapData.bombermans.push_back(bomberman);
    }

    const auto& botArray = json["bot_respawns"].toArray();
    for (size_t i = 0; i < botArray.size(); ++i) {
        auto index = botArray[i].toInt();
        auto bot   = createBot(BotType::Regular, *mapData.map);
        bot->setCoordinates(mapData.map->indexToCellCenterCoordinates(index));
        mapData.bots.push_back(std::move(bot));
    }
}

} // namespace

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

        map->setRespawnPlaces(RespawnType::Bot, { 11, 18 });

        return map;
    } catch (...) {
        return nullptr;
    }
}

MapData loadFromFile(const QString& filePath)
{
    qDebug() << filePath;
    QFile file { filePath };
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }

    auto            jsonData = file.readAll();
    QJsonParseError error;
    auto            document = QJsonDocument::fromJson(jsonData, &error);
    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing json:" << error.errorString();
        return {};
    }

    const auto& jsonObject = document.object();
    size_t      width      = jsonObject["width"].toInt(0);
    size_t      height     = jsonObject["height"].toInt(0);
    if (width == 0 || height == 0) {
        return {};
    }

    try {
        auto        map          = std::make_unique<Map>(width, height);
        const auto& mapJsonArray = jsonObject["map"].toArray();
        if (mapJsonArray.size() != width * height) {
            return {};
        }

        for (qsizetype i = 0; i < mapJsonArray.size(); ++i) {
            map->setCellType(static_cast<size_t>(i), jsonValueToCellStructure(mapJsonArray[i].toInt()));
        }

        MapData mapData;
        mapData.map = std::move(map);

        parseRespawnLocations(jsonObject, mapData);

        return mapData;
    } catch (const std::exception& e) {
        return {};
    }

    qDebug() << width << height;
}

} // namespace map_loader
} // namespace bm
