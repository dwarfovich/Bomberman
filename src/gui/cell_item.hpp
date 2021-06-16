#ifndef CELLITEM_HPP
#define CELLITEM_HPP

#include <QGraphicsItem>
#include <QBrush>

namespace bm {
struct Cell;

namespace gui {
    class CellItem : public QGraphicsItem {
    public:
        explicit CellItem(const Cell* cell = nullptr, QGraphicsItem* parent = nullptr);
        CellItem(const CellItem&) = delete;
        CellItem& operator=(const CellItem&) = delete;

        CellItem(CellItem&& other);
        CellItem& operator=(CellItem&& rhs);

    private:
        const Cell* cell_;
        static double size_;
        static const QBrush concreteBrush_;
        static const QBrush bricksBrush_;
        // QGraphicsItem interface
    public:
        QRectF boundingRect() const override;
        void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
    };
}  // namespace gui
}  // namespace bm

#endif  // CELLITEM_HPP
