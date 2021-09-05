#include "explosion_sprite_item.hpp"

namespace bm {
namespace gui {

ExplosionSpriteItem::ExplosionSpriteItem(const SpriteItemCallbacks *callbacks, const QPixmap &pixmap)
    : SpriteItem { callbacks, pixmap }
{}

void ExplosionSpriteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    SpriteItem::paint(painter, option, widget);
}

void ExplosionSpriteItem::addExplosionPart(std::unique_ptr<SpriteItem> part)
{
    part->setParentItem(this);
    explosionParts_.push_back(std::move(part));
}

void ExplosionSpriteItem::advance(int phase)
{
    SpriteItem::advance(phase);
    for (const auto &part : explosionParts_) {
        part->advance(phase);
    }
}

} // namespace gui
} // namespace bm
