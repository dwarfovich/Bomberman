#ifndef BM_SPRITEFACTORY_HPP
#define BM_SPRITEFACTORY_HPP

#include "sprite_graphics_object.hpp"

#include <memory>

namespace bm {
class Cell;
class Bomberman;
class Bot;

namespace gui {

class SpriteObjectFactory
{
public:
    SpriteObjectFactory();

    std::unique_ptr<SpriteGraphicsObject> createCellObject(const Cell* cell);
    std::unique_ptr<SpriteGraphicsObject> createBombermanObject(const std::shared_ptr<Bomberman>& character);

private:
    QPixmap cell_;
    QPixmap bomberman_;
    QPixmap bot_;
};

// std::unique_ptr<SpriteGraphicsObject> createCellObject(const Cell *cell);

} // namespace gui
} // namespace bm

#endif // BM_SPRITEFACTORY_HPP
