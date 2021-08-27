#include "animated_sprite_graphics_object.hpp"

namespace bm {
namespace gui {

AnimatedSpriteGraphicsObject::AnimatedSpriteGraphicsObject(QGraphicsItem* parent) : SpriteGraphicsObject { parent }
{}

bool AnimatedSpriteGraphicsObject::isAnimated() const
{
    return true;
}

void AnimatedSpriteGraphicsObject::setCurrentFrame(int frame)
{
    currentFrame_   = frame;
    pixmapFragment_ = QPainter::PixmapFragment::create(
        { cellHalfSizeF, cellHalfSizeF },
        { currentFrame_ * cellSizeF, currentSpriteRow_ * cellSizeF, cellSizeF, cellSizeF });
    emit currentFrameChanged();
    update();
}

void AnimatedSpriteGraphicsObject::setCharacter(const std::shared_ptr<Character>& newCharacter)
{
    character_ = newCharacter;
}

void AnimatedSpriteGraphicsObject::updateSpriteMapRow()
{
    switch (character_->direction()) {
        case Direction::Upward: currentSpriteRow_ = 0; break;
        case Direction::Right: currentSpriteRow_ = 1; break;
        case Direction::Downward: currentSpriteRow_ = 2; break;
        case Direction::Left: currentSpriteRow_ = 3; break;
    }
    pixmapFragment_ = QPainter::PixmapFragment::create(
        { cellHalfSizeF, cellHalfSizeF },
        { currentFrame_ * cellSizeF, currentSpriteRow_ * cellSizeF, cellSizeF, cellSizeF });
    update();
}

} // namespace gui
} // namespace bm
