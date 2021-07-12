#ifndef MAP_HPP
#define MAP_HPP

#include "cell.hpp"
#include "bomberman.hpp"
#include "enemy.hpp"
#include "cell_type.hpp"
#include "bomb.hpp"

#include <QObject>
#include <QPoint>

#include <vector>

namespace bm {
inline const size_t wrongIndex = -1;

class Map : public QObject
{
    Q_OBJECT

public:
    Map() = default;
    Map(size_t width, size_t height);

    bool reset(size_t width, size_t height);
    void setCellType(size_t index, CellType type);
    bool placeBomb(const std::shared_ptr<Bomb>& bomb);
    void removeBomb(size_t index);
    void setPlayer(const std::shared_ptr<Bomberman>& player);
    bool moveCharacter(const std::shared_ptr<Character>& character, Direction direction);
    void stopCharacter(const std::shared_ptr<Character>& character, Direction direction);

    QPoint                     indexToCoordinates(size_t index) const;
    size_t                     coordinatesToIndex(const QPoint& point) const;
    bool                       nextCellIsMovable(const Character& object, Direction direction) const;
    bool                       nextCellIsMovable(const QPoint& location, Direction direction) const;
    bool                       isProperIndex(size_t index) const;
    size_t                     width() const;
    size_t                     height() const;
    const std::vector<Cell>&   map() const;
    const std::vector<QPoint>& bombs() const;
    QPoint                     cellIndexToCenterLocation(size_t index) const;

    const std::shared_ptr<Bomberman>& player() const;

    const std::vector<std::shared_ptr<Bomberman>>& bombermans() const;

    const std::vector<std::shared_ptr<Enemy>>& enemies() const;

    void moveObjects(double timeDelta);

    size_t cellSize() const;

signals:
    void cellChanged(size_t index);
    void characterMoved(const std::shared_ptr<Character>& character);

private: // methods
    size_t shiftIndex(size_t index, Direction direction) const;
    int    alignToCellCenter(int position) const;

private: // data
    int cellSize_ = 50;
    // int                                     halfCellSize_  = cellSize_ / 2;
    size_t                                  widthInCells_  = 0;
    size_t                                  heightInCells_ = 0;
    std::vector<Cell>                       map_;
    std::vector<std::shared_ptr<Bomberman>> bombermans_;
    std::shared_ptr<Bomberman>              player_;
    std::vector<std::shared_ptr<Enemy>>     enemies_;
    std::vector<std::shared_ptr<Bomb>>      bombs_;
};
} // namespace bm

#endif // MAP_HPP
