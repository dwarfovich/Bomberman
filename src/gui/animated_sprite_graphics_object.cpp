#include "animated_sprite_graphics_object.hpp"

namespace bm {
namespace gui {

AnimatedSpriteGraphicsObject::AnimatedSpriteGraphicsObject(QGraphicsItem *parent) : SpriteGraphicsObject { parent }
{}

bool AnimatedSpriteGraphicsObject::isAnimated() const
{
    return true;
}

void AnimatedSpriteGraphicsObject::setCurrentFrame(int frame)
{
    pixmapFragment_ = QPainter::PixmapFragment::create(
        { cellHalfSizeF, cellHalfSizeF },
        { currentFrame_ * cellSizeF, currentSpriteRow_ * cellSizeF, cellSizeF, cellSizeF });
    emit currentFrameChanged();
    update();
}

} // namespace gui
} // namespace bm
