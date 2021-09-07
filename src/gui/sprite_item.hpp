#ifndef BM_SPRITEITEM_HPP
#define BM_SPRITEITEM_HPP

#include "sprite_item_callbacks.hpp"

#include <QGraphicsItem>
#include <QPainter>

namespace bm {
namespace gui {

namespace sprite_ns {
inline constexpr int    cellSize      = 50;
inline constexpr int    cellHalfSize  = cellSize / 2;
inline constexpr qreal  cellSizeF     = 50.;
inline constexpr qreal  cellHalfSizeF = cellSizeF / 2.;
inline constexpr QRectF spriteBoundingRect { 0, 0, cellSizeF, cellSizeF };
} // namespace sprite_ns

class SpriteItem : public QGraphicsItem
{
public:
    SpriteItem(const SpriteItemCallbacks* callbacks = nullptr, const QPixmap& pixmap = {});

    QRectF boundingRect() const override;
    void   paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    void   advance(int phase) override;

    virtual void updateSprite();
    virtual bool hasDestroyAnimation() const;
    virtual void startDestroyAnimation();

    void setPixmap(const QPixmap& newPixmap);
    void setCallbacks(const SpriteItemCallbacks* newCallbacks);
    void setCurrentSpriteRow(int newCurrentSpriteRow);
    void setCurrentFrame(int newCurrentFrame);
    void setFramesCount(int count);
    void setNotifyOnLastFrameShowed(bool newNotifyOnLastFrameShowed);
    void updatePixmapFragment();

protected:
    const SpriteItemCallbacks* callbacks_;
    QPixmap                    pixmap_;
    QPainter::PixmapFragment   pixmapFragment_;
    int                        currentSpriteRow_        = 0;
    int                        currentFrame_            = 0;
    int                        framesCount_             = 1;
    bool                       notifyOnLastFrameShowed_ = false;
};

} // namespace gui
} // namespace bm

#endif // BM_SPRITEITEM_HPP
