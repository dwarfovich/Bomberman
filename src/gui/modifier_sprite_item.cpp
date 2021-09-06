#include "modifier_sprite_item.hpp"

namespace bm {
namespace gui {

ModifierSpriteItem::ModifierSpriteItem(const SpriteItemCallbacks *callbacks, const QPixmap &pixmap)
    : SpriteItem { callbacks, pixmap }
{}

} // namespace gui
} // namespace bm
