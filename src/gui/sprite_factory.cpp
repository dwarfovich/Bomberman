#include "sprite_factory.hpp"
#include "cell_item.hpp"
#include "animated_sprite_graphics_object.hpp"
#include "game/character.hpp"

namespace bm {
namespace gui {

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createCellObject(const Cell *cell)
{
    auto item = std::make_unique<CellItem>(cell);

    return item;
}

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBombermanObject(
    const std::shared_ptr<Bomberman> &character)
{
    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
    item->setPixmap(bomberman_);

    return item;
}

} // namespace gui
} // namespace bm
