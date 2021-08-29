#ifndef BM_GUI_SPRITEGRAPHICSOBJECT_HPP
#define BM_GUI_SPRITEGRAPHICSOBJECT_HPP

#include <QGraphicsObject>
#include <QPainter>

namespace bm {
namespace gui {

inline const qreal  cellSizeF     = 50.;
inline const qreal  cellHalfSizeF = cellSizeF / 2.;
inline const int    cellSize      = cellSizeF;
inline const int    cellHalfSize  = cellSize / 2;
inline const QRectF spriteBoundingRect { 0, 0, cellSizeF, cellSizeF };

class SpriteGraphicsObject : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(int SpriteFrame MEMBER currentFrame_ READ currentFrame WRITE setCurrentFrame NOTIFY currentFrameChanged);

public:
    explicit SpriteGraphicsObject(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void   paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void updateSpriteMapRow();
    virtual bool isAnimated() const;
    virtual bool isAnimatedDestroy() const;
    virtual int  currentFrame() const;
    virtual void setCurrentFrame(int frame);
    virtual int  framesCount() const;
    virtual int  currentSpriteRow() const;

    void setPixmap(const QPixmap &pixmap);

signals:
    void currentFrameChanged();
    void startAnimation(bm::gui::SpriteGraphicsObject *sprite);
    void stopAnimation(bm::gui::SpriteGraphicsObject *sprite);

protected:
    QPixmap                  pixmap_;
    QPainter::PixmapFragment pixmapFragment_;
    int                      currentFrame_ = 0;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_SPRITEGRAPHICSOBJECT_HPP
