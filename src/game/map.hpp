#ifndef MAP_HPP
#define MAP_HPP

#include "cell.hpp"
#include "bomberman.hpp"
#include "enemy.hpp"
#include "cell_type.hpp"

#include <QObject>
#include <QPoint>

#include <vector>

namespace bm {
inline const size_t wrongIndex = -1;

class Map : public QObject {
    Q_OBJECT

public:
    Map() = default;
    Map(size_t width, size_t height);

    bool reset(size_t width, size_t height);
    void setCellType(size_t index, CellType type);
    bool placeBomb(size_t index);
    void removeBomb(size_t index);
    void setPlayer(const std::shared_ptr<Bomberman>& player);
    bool moveCharacter(Character& object, Direction direction);

    QPoint indexToCoordinates(size_t index) const;
    size_t coordinatesToIndex(const QPoint& point) const;
    bool canMoveCharacter(const Character& object, Direction direction) const;
    bool isProperIndex(size_t index) const;
    size_t width() const;
    size_t height() const;
    const std::vector<Cell>& map() const;
    const std::vector<QPoint>& bombs() const;

    const std::shared_ptr<Bomberman>& player() const;

signals:
    void cellChanged(size_t index);

private:
    size_t width_ = 0;
    size_t height_ = 0;
    std::vector<Cell> map_;
    std::vector<QPoint> bombs_;
    std::vector<std::shared_ptr<Bomberman> > bombermans_;
    std::shared_ptr<Bomberman> player_;
    std::vector<Enemy> enemies_;
};
}  // namespace bm

#endif  // MAP_HPP
