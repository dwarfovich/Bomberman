#include "bot_graphics_item.hpp"

#include <QPainter>

namespace bm {
namespace gui {

void BotGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-25, -25, 50, 50);
    QString d;
    switch (character_->movementData().direction) {
        case Direction::Upward: d = "Up"; break;
        case Direction::Right: d = "Right"; break;
        case Direction::Downward: d = "Down"; break;
        case Direction::Left: d = "Left"; break;
    }
    painter->drawText(-20, 0, d);
    QString l = QString::number(character_->movementData().coordinates.x());
    l += ", ";
    l += QString::number(character_->movementData().coordinates.y());
    painter->drawText(-20, 20, l);
}

} // namespace gui
} // namespace bm
