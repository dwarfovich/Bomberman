#include "sprite_factory.hpp"
#include "cell_item.hpp"
#include "animated_sprite_graphics_object.hpp"
#include "game/character.hpp"
#include "game/bomberman.hpp"

namespace bm {
namespace gui {

SpriteObjectFactory::SpriteObjectFactory()
{
    bomberman_ = QPixmap { QStringLiteral(":/gfx/bomberman.png") };
}

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
    item->setCharacter(character);

    return item;
}

} // namespace gui
} // namespace bm
