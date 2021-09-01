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

void AnimatedSpriteGraphicsObject::advanceFrame()
{
    if (destroyAnimationSpriteRow_ == currentSpriteRow_ && currentFrame_ == framesCount() - 1) {
        destroyAnimationFinishedCallback_(this);
        return;
    }

    if (currentFrame_ == framesCount() - 1) {
        currentFrame_ = 0;
    } else {
        ++currentFrame_;
    }
    pixmapFragment_ = QPainter::PixmapFragment::create(
        { cellHalfSizeF, cellHalfSizeF },
        { currentFrame_ * cellSizeF, currentSpriteRow_ * cellSizeF, cellSizeF, cellSizeF });
    update();
}

int AnimatedSpriteGraphicsObject::destroyAnimationSpriteRow() const
{
    return destroyAnimationSpriteRow_;
}

void AnimatedSpriteGraphicsObject::setDestroyAnimationSpriteRow(int newDestroyAnimationSpriteRow)
{
    destroyAnimationSpriteRow_ = newDestroyAnimationSpriteRow;
}

void AnimatedSpriteGraphicsObject::setFramesCount(int newFramesCount)
{
    framesCount_ = newFramesCount;
}

void AnimatedSpriteGraphicsObject::setCharacter(const std::shared_ptr<Character>& newCharacter)
{
    character_ = newCharacter;
}

void AnimatedSpriteGraphicsObject::setSpriteRow(int row)
{
    currentSpriteRow_ = row;
    pixmapFragment_   = QPainter::PixmapFragment::create(
        { cellHalfSizeF, cellHalfSizeF },
        { currentFrame_ * cellSizeF, currentSpriteRow_ * cellSizeF, cellSizeF, cellSizeF });

    update();
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

    if (animationInProgress && character_->speed() == 0) {
        animationInProgress = false;
        setCurrentFrame(0);
        emit stopAnimation(this);
    } else if (!animationInProgress && character_->speed() != 0) {
        animationInProgress = true;
        emit startAnimation(this);
    }

    update();
}

void AnimatedSpriteGraphicsObject::advance(int phase)
{
    if (phase == 1) {
        advanceFrame();
    }
}

int AnimatedSpriteGraphicsObject::framesCount() const
{
    return framesCount_;
}

void AnimatedSpriteGraphicsObject::startDestroyAnimation()
{
    if (destroyAnimationSpriteRow_ != -1) {
        setSpriteRow(destroyAnimationSpriteRow_);
        setCurrentFrame(0);
        update();
    } else {
        destroyAnimationFinishedCallback_(this);
    }
}

} // namespace gui
} // namespace bm
