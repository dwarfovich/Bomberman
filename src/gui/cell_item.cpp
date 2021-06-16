#include "cell_item.hpp"
#include "game/cell.hpp"

#include <QPainter>

namespace bm {
namespace gui {
    double CellItem::size_ = 50;
    const QBrush CellItem::concreteBrush_ = Qt::gray;
    const QBrush CellItem::bricksBrush_ = QColor(150, 0, 0);

    CellItem::CellItem(const Cell* cell, QGraphicsItem* parent) : QGraphicsItem{parent}, cell_{cell}
    {
    }

    CellItem::CellItem(CellItem&& other)
    {
        cell_ = other.cell_;
        other.cell_ = nullptr;
    }

    CellItem& CellItem::operator=(CellItem&& rhs)
    {
        cell_ = rhs.cell_;
        rhs.cell_ = nullptr;

        return (*this);
    }

    QRectF CellItem::boundingRect() const
    {
        return {0., 0., size_, size_};
    }

    void CellItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
    {
        if (cell_->type != CellType::Empty) {
            if (cell_->type == CellType::Concrete) {
                painter->setBrush(concreteBrush_);
            }
            else if (cell_->type == CellType::Destroyable) {
                painter->setBrush(bricksBrush_);
            }
            painter->drawRect(boundingRect());
        }
        else {
            if (cell_->hasBomb) {
                painter->setBrush(Qt::red);
                painter->drawEllipse(boundingRect());
            }
        }
    }
}  // namespace gui
}  // namespace bm
