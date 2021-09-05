#ifndef BM_GUI_CELLSPRITEITEM_HPP
#define BM_GUI_CELLSPRITEITEM_HPP

#include "sprite_item.hpp"

namespace bm {
namespace gui {

class CellSpriteItem : public SpriteItem
{
public:
    enum class AnimationType : uint8_t
    {
        Static = 0,
        BricksDestroying,
        ConcreteToBricksDestroying,
    };

    enum class CellStructureFrame : uint8_t
    {
        Empty = 0,
        Bricks,
        Concrete,
    };

    CellSpriteItem(const SpriteItemCallbacks* callbacks = {}, const QPixmap& pixmap = {});

    void setAnimationType(AnimationType type);
    void setStructureFrame(CellStructureFrame structure);
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_CELLSPRITEITEM_HPP
