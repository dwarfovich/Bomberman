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

    friend QDataStream& operator<<(QDataStream& stream, const Map& map);
    friend QDataStream& operator>>(QDataStream& stream, Map& map);

    Map() = default;
    Map(size_t width, size_t height);

    bool reset(size_t width, size_t height);
    void setCellType(size_t index, CellStructure structure);
    void setCell(const Cell& cell);
    bool placeBomb(const std::shared_ptr<Bomb>& bomb);
    bool removeBomb(size_t index);
    bool setModifier(size_t index, const std::shared_ptr<IModifier>& modifier);
    void addBomberman(const std::shared_ptr<Bomberman>& bomberman);
    void removeBomberman(const Bomberman& bomberman);
    void addBot(const std::shared_ptr<Bot>& bot);
    void moveCharacter(uint8_t id, const MoveData& moveData) const;
    void addExplosion(const std::shared_ptr<Explosion>& explosion);
    void removeExplosion(const std::shared_ptr<Explosion>& explosion);
    // void                                 addMovingObject(const std::shared_ptr<MovingObject>& object);
    void                                 removeMovingObject(const std::shared_ptr<MovingObject>& object);
    void                                 removeMovingObject(const MovingObject& object);
    const std::shared_ptr<MovingObject>& sharedPtrForObject(const MovingObject& object) const;

    const Cell&              cell(size_t index) const;
    CellLocation             coordinatesToLocation(const QPoint& coordinates) const;
    QPoint                   indexToCoordinates(size_t index) const;
    QPoint                   locationToCellCenterCoordinates(const CellLocation& location) const;
    size_t                   coordinatesToIndex(const QPoint& point) const;
    size_t                   locationToIndex(const CellLocation& location) const;
    CellLocation             indexToLocation(size_t index) const;
    QPoint                   indexToCellCenterCoordinates(size_t index) const;
    bool                     isCellCenter(const QPoint& coordinates) const;
    bool                     cellIsMovable(const CellLocation& location) const;
    bool                     nextCellIsMovable(const MovingObject& object, Direction direction) const;
    bool                     nextCellIsMovable(const QPoint& coordinates, Direction direction) const;
    bool                     isProperIndex(size_t index) const;
    size_t                   width() const;
    size_t                   height() const;
    const std::vector<Cell>& cells() const;
    const RespawnPlaces&     playerRespawns() const;

    void addGameObjectsForCell(const CellLocation& location, std::vector<GameObject*>& objects);
    void addGameObjectsForCell(size_t index, std::vector<GameObject*>& objects);

    void moveObjects(double timeDelta);

    const RespawnPlaces& respawnPlaces(RespawnType type) const;
    void                 setRespawnPlaces(RespawnType type, const RespawnPlaces& places);

    const BombermansMap& bombermans() const { return bombermans_; }

    const std::vector<std::shared_ptr<Bot>>& bots() const;

    uint32_t randomSeed() const;

signals:
    void cellChanged(size_t index);
    void objectMoved(const std::shared_ptr<MovingObject>& object);
    // void objectAdded(const std::shared_ptr<MovingObject>& object);
    void objectIndexChanged(const std::shared_ptr<MovingObject>& bomberman, size_t index);
    void characterMeetsModifier(const std::shared_ptr<Bomberman>& bomberman, size_t cellIndex);
    void objectsCollided(bm::GameObject& lhs, bm::GameObject& rhs);

private: // methods
    void checkCollisions();
    bool objectsIntersect(MovingObject& lhs, MovingObject& rhs);

    size_t shiftIndex(size_t index, Direction direction) const;
    int    alignToCellCenter(int position) const;

    QPoint       coordinatesInCell(const QPoint& coordinates) const;
    void         alignToCenter(double timeDelta, Character& character);
    CellLocation upperRightLocation(const CellLocation& location) const;
    CellLocation upperLeftLocation(const CellLocation& location) const;
    CellLocation shiftLocation(const CellLocation& location, int dx, int dy) const;
    bool         circlesIntersect(const QPoint& center1, const QPoint& center2) const;
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
    uint32_t                                                   randomSeed_    = 0;
    size_t                                                     widthInCells_  = 0;
    size_t                                                     heightInCells_ = 0;
    std::vector<Cell>                                          cells_;
    std::vector<std::shared_ptr<MovingObject>>                 movingObjects_;
    std::unordered_map<uint8_t, std::shared_ptr<MovingObject>> idToMovingObjects_;
    BombermansMap                                              bombermans_;
    std::vector<std::shared_ptr<Bot>>                          bots_;
    std::vector<std::shared_ptr<Bomb>>                         bombs_;
    std::vector<std::shared_ptr<Explosion>>                    explosions_;
    std::unordered_map<RespawnType, RespawnPlaces>             respawnPlaces_;
};

} // namespace bm

#endif // MAP_HPP
