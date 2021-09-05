#include "cell_sprite_item.hpp"

namespace bm {
namespace gui {

CellSpriteItem::CellSpriteItem(const SpriteItemCallbacks *callbacks, const QPixmap &pixmap)
    : SpriteItem { callbacks, pixmap }
{}

void CellSpriteItem::setAnimationType(AnimationType type)
{
    setCurrentSpriteRow(static_cast<uint8_t>(type));
    setCurrentFrame(0);
}

void CellSpriteItem::setStructureFrame(CellStructureFrame structure)
{
    setCurrentFrame(static_cast<uint8_t>(structure));
}

} // namespace gui
} // namespace bm
