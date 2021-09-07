#ifndef BM_GUI_MODIFIERSPRITEITEM_HPP
#define BM_GUI_MODIFIERSPRITEITEM_HPP

#include "sprite_item.hpp"

namespace bm {
namespace gui {

class ModifierSpriteItem : public SpriteItem
{
public:
    ModifierSpriteItem(const SpriteItemCallbacks *callbacks = nullptr, const QPixmap &pixmap = {});
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_MODIFIERSPRITEITEM_HPP
