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

void CellSpriteItem::advance(int phase)
{
    if (currentFrame_ < framesCount_ - 1) {
        ++currentFrame_;
    } else {
        if (currentSpriteRow_ == static_cast<uint8_t>(AnimationType::BricksDestroying)) {
            setStructureFrame(CellStructureFrame::Empty);
        } else if (currentSpriteRow_ == static_cast<uint8_t>(AnimationType::ConcreteToBricksDestroying)) {
            setStructureFrame(CellStructureFrame::Bricks);
        }
        currentSpriteRow_ = 0;
        callbacks_->animationFinished(this);
    }

    updatePixmapFragment();
}

} // namespace gui
} // namespace bm
