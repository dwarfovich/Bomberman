#include "sprite_item.hpp"

namespace bm {

namespace gui {
SpriteItem::SpriteItem(const SpriteItemCallbacks *callbacks, const QPixmap &pixmap)
    : callbacks_ { callbacks }, pixmap_ { pixmap }
{
    updatePixmapFragment();
}

void SpriteItem::setPixmap(const QPixmap &newPixmap)
{
    pixmap_ = newPixmap;
    updatePixmapFragment();
}

void SpriteItem::setCallbacks(const SpriteItemCallbacks *newCallbacks)
{
    callbacks_ = newCallbacks;
}

void SpriteItem::setCurrentSpriteRow(int newCurrentSpriteRow)
{
    currentSpriteRow_ = newCurrentSpriteRow;
    updatePixmapFragment();
}

void SpriteItem::setCurrentFrame(int newCurrentFrame)
{
    currentFrame_ = newCurrentFrame;
    updatePixmapFragment();
}

void SpriteItem::setFramesCount(int count)
{
    framesCount_ = count;
}

void SpriteItem::setNotifyOnLastFrameShowed(bool newNotifyOnLastFrameShowed)
{
    notifyOnLastFrameShowed_ = newNotifyOnLastFrameShowed;
}

void SpriteItem::updatePixmapFragment()
{
    using namespace sprite_ns;
    pixmapFragment_ = QPainter::PixmapFragment::create(
        { cellHalfSizeF, cellHalfSizeF },
        { currentFrame_ * cellSizeF, currentSpriteRow_ * cellSizeF, cellSizeF, cellSizeF });
}

QRectF SpriteItem::boundingRect() const
{
    return sprite_ns::spriteBoundingRect;
}

void SpriteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmapFragments(&pixmapFragment_, 1, pixmap_);
}

void SpriteItem::advance(int phase)
{
    // TODO: check why we need - 1 here.
    if (currentFrame_ < framesCount_ - 1) {
        ++currentFrame_;
    } else {
        currentFrame_ = 0;
    }

    updateSprite();
    update();
}

void SpriteItem::updateSprite()
{
    updatePixmapFragment();
}

bool SpriteItem::hasDestroyAnimation() const
{
    return false;
}

void SpriteItem::startDestroyAnimation()
{}

} // namespace gui

} // namespace bm
