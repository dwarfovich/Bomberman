#ifndef MAP_HPP
#define MAP_HPP

#include "cell.hpp"
#include "bomberman.hpp"
#include "bot.hpp"
#include "cell_structure.hpp"
#include "bomb.hpp"
#include "explosion.hpp"
#include "respawn_type.hpp"

#include <QObject>
#include <QPoint>

#include <vector>
#include <unordered_set>

namespace bm {
class CellLocation;

class Map : public QObject
{
    Q_OBJECT

public:
    using RespawnPlaces = std::vector<size_t>;
    using BombermansMap = std::unordered_map<const Bomberman*, std::shared_ptr<Bomberman>>;
    using CollisionPair = std::pair<std::shared_ptr<GameObject>, std::shared_ptr<GameObject>>;
    using Collisions    = std::vector<CollisionPair>;

    friend QDataStream& operator<<(QDataStream& stream, const Map& map);
    friend QDataStream& operator>>(QDataStream& stream, Map& map);

    Map() = default;
    Map(size_t width, size_t height);

    bool                              reset(size_t width, size_t height);
    void                              setCellType(size_t index, CellStructure structure);
    void                              setCell(const Cell& cell);
    bool                              placeBomb(const std::shared_ptr<Bomb>& bomb);
    bool                              removeBomb(size_t index);
    bool                              setModifier(size_t index, const std::shared_ptr<IModifier>& modifier);
    void                              addBomberman(const std::shared_ptr<Bomberman>& bomberman);
    void                              removeBomberman(const Bomberman& bomberman);
    const std::shared_ptr<Bomberman>& bomberman(object_id_t id) const;
    void                              addBot(const std::shared_ptr<Bot>& bot);
    void                              removeBot(const std::shared_ptr<Bot>& bot);
    void                              moveCharacter(object_id_t id, const MoveData& moveData) const;
    void                              removeCharacter(object_id_t id);
    void                              addExplosion(const std::shared_ptr<Explosion>& explosion);
    void                              removeExplosion(const std::shared_ptr<Explosion>& explosion);
    const std::shared_ptr<Character>& character(object_id_t id) const;

    const Cell&                               cell(size_t index) const;
    CellLocation                              coordinatesToLocation(const QPoint& coordinates) const;
    QPoint                                    indexToCoordinates(size_t index) const;
    QPoint                                    locationToCellCenterCoordinates(const CellLocation& location) const;
    size_t                                    coordinatesToIndex(const QPoint& point) const;
    size_t                                    locationToIndex(const CellLocation& location) const;
    CellLocation                              indexToLocation(size_t index) const;
    QPoint                                    indexToCellCenterCoordinates(size_t index) const;
    bool                                      isCellCenter(const QPoint& coordinates) const;
    bool                                      cellIsMovable(const CellLocation& location) const;
    bool                                      nextCellIsMovable(const Character& character, Direction direction) const;
    bool                                      nextCellIsMovable(const QPoint& coordinates, Direction direction) const;
    bool                                      isProperIndex(size_t index) const;
    size_t                                    width() const;
    size_t                                    height() const;
    const std::vector<std::shared_ptr<Cell>>& cells() const;
    const RespawnPlaces&                      playerRespawns() const;

    void addGameObjectsForCell(size_t index, std::vector<GameObject*>& objects);

    void moveObjects(double timeDelta);

    const RespawnPlaces& respawnPlaces(RespawnType type) const;
    void                 setRespawnPlaces(RespawnType type, const RespawnPlaces& places);

    const BombermansMap& bombermans() const { return bombermans_; }

    const std::vector<std::shared_ptr<Bot>>& bots() const;

    uint32_t randomSeed() const;

signals:
    void cellStructureChanged(size_t index, CellStructure previousStructure);
    void characterMoved(const std::shared_ptr<Character>& character);
    void characterIndexChanged(const std::shared_ptr<Character>& character, size_t index);
    void characterMeetsModifier(const std::shared_ptr<Bomberman>& bomberman, size_t cellIndex);
    void objectsCollided(const Map::Collisions& collisions);
    void modifierAdded(size_t index, const std::shared_ptr<IModifier>& modifier);
    void modifierRemoved(size_t index, const std::shared_ptr<IModifier>& modifier);

private: // methods
    void checkBombermanAndBotCollisions(Collisions& collisions);
    void checkExplosionCollisions(Collisions& collisions);
    bool charactersIntersect(const Character& lhs, const Character& rhs) const;
    void addExplosionCollisionsAtLocation(const CellLocation&               location,
                                          const std::shared_ptr<Explosion>& explosion,
                                          Collisions&                       collisions);

    size_t shiftIndex(size_t index, Direction direction) const;
    int    alignToCellCenter(int position) const;

    QPoint       topLeftCoordinates(const QPoint& coordinates) const;
    void         alignToCenter(double timeDelta, Character& character);
    CellLocation upperRightLocation(const CellLocation& location) const;
    CellLocation upperLeftLocation(const CellLocation& location) const;
    CellLocation shiftLocation(const CellLocation& location, int dx, int dy) const;
    bool         circlesIntersect(const QPoint& center1, const QPoint& center2) const;
    bool         rectsIntersect(const QPoint& center1, const QPoint& center2) const;
    int          moveCoordinateY(int y, int speed, int timeDelta) const;
    int          findXObstacle(const QPoint& coordinates, Direction direction) const;
    int          findYObstacle(const QPoint& coordinates, Direction direction) const;

    QPoint findUpwardRightObstacle(const QPoint& coordinates) const;
    QPoint findUpwardLeftObstacle(const QPoint& coordinates) const;
    QPoint findRightTopObstacle(const QPoint& coordinates) const;
    QPoint findRightBottomObstacle(const QPoint& coordinates) const;
    QPoint findDownwardRightObstacle(const QPoint& coordinates) const;
    QPoint findDownwardLeftObstacle(const QPoint& coordinates) const;
    QPoint findLeftBottomObstacle(const QPoint& coordinates) const;
    QPoint findLeftTopObstacle(const QPoint& coordinates) const;

    int firstCoordinateObstacle(const QPoint& coordinates, Direction direction) const;
    int inCellCoordinate(const QPoint& coordinates, Direction direction);

private: // data
    uint32_t                           randomSeed_    = 0;
    size_t                             widthInCells_  = 0;
    size_t                             heightInCells_ = 0;
    std::vector<std::shared_ptr<Cell>> cells_;
    using IdCharactersMap = std::unordered_map<object_id_t, std::shared_ptr<Character>>;
    IdCharactersMap                                idToCharacterMap_;
    BombermansMap                                  bombermans_;
    std::vector<std::shared_ptr<Bot>>              bots_;
    std::vector<std::shared_ptr<Bomb>>             bombs_;
    std::vector<std::shared_ptr<Explosion>>        explosions_;
    std::unordered_map<RespawnType, RespawnPlaces> respawnPlaces_;
};

} // namespace bm

#endif // MAP_HPP
