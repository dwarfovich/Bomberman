#include "sprite_graphics_object.hpp"

namespace bm {
namespace gui {

SpriteGraphicsObject::SpriteGraphicsObject(QGraphicsItem *parent) : QGraphicsObject { parent }
{}

QRectF SpriteGraphicsObject::boundingRect() const
{
    return spriteBoundingRect;
}

void SpriteGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmapFragments(&pixmapFragment_, 1, pixmap_);
}

void SpriteGraphicsObject::updateSpriteMapRow()
{}

bool SpriteGraphicsObject::isAnimated() const
{
    return false;
}

bool SpriteGraphicsObject::isAnimatedDestroy() const
{
    return false;
}

int SpriteGraphicsObject::currentFrame() const
{
    return 0;
}

void SpriteGraphicsObject::setCurrentFrame(int frame)
{
    Q_UNUSED(frame);
}

int SpriteGraphicsObject::framesCount() const
{
    return 1;
}

void SpriteGraphicsObject::setPixmap(const QPixmap &pixmap)
{
    pixmap_         = pixmap;
    pixmapFragment_ = QPainter::PixmapFragment::create({ cellHalfSizeF, cellHalfSizeF },
                                                       { currentFrame_ * cellSizeF, 0., cellSizeF, cellSizeF });
}

} // namespace gui
} // namespace bm
