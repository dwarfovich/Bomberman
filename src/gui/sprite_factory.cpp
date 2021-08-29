#include "sprite_factory.hpp"
#include "cell_item.hpp"
#include "animated_sprite_graphics_object.hpp"
#include "explosion_graphics_object.hpp"
#include "game/character.hpp"
#include "game/bomberman.hpp"
#include "game/bot.hpp"

namespace bm {
namespace gui {

SpriteObjectFactory::SpriteObjectFactory()
{
    bomberman_ = QPixmap { QStringLiteral(":/gfx/bomberman.png") };
    bot_       = QPixmap { QStringLiteral(":/gfx/bot.png") };
    bomb_      = QPixmap { QStringLiteral(":/gfx/bomb.png") };
    explosion_ = QPixmap { QStringLiteral(":/gfx/explosion.png") };
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

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBotObject(const std::shared_ptr<Bot> &character)
{
    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
    item->setPixmap(bot_);
    item->setCharacter(character);

    return item;
}

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createBombObject(const std::shared_ptr<Bomb> &bomb)
{
    auto item = std::make_unique<AnimatedSpriteGraphicsObject>();
    item->setPixmap(bomb_);
    item->setFramesCount(4);

    return item;
}

std::unique_ptr<SpriteGraphicsObject> SpriteObjectFactory::createExplosionObject(const Explosion *explosion)
{
    auto item = std::make_unique<ExplosionGraphicsObject>(explosion);
    item->setPixmap(explosion_);
    item->setFramesCount(4);

    return item;
}

} // namespace gui
} // namespace bm
