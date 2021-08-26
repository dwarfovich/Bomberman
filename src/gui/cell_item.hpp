#ifndef CELLITEM_HPP
#define CELLITEM_HPP

#include "sprite_graphics_object.hpp"

#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QBrush>

namespace bm {
class Cell;

namespace gui {

class CellItem : public SpriteGraphicsObject
{
public:
    explicit CellItem(const Cell* cell = nullptr, QGraphicsItem* parent = nullptr);
    CellItem(const CellItem&) = delete;
    CellItem& operator=(const CellItem&) = delete;
    CellItem(CellItem&& other);
    CellItem& operator=(CellItem&& rhs);

    QRectF boundingRect() const override;
    void   paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    const Cell*         cell_;
    static double       size_;
    static const QBrush concreteBrush_;
    static const QBrush bricksBrush_;
};

} // namespace gui
} // namespace bm

#endif // CELLITEM_HPP
