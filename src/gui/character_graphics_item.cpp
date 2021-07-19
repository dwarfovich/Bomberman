#include "character_graphics_item.hpp"

#include <QPainter>

namespace bm {
namespace gui {

CharacterGraphicsItem::CharacterGraphicsItem()
{}

QRectF CharacterGraphicsItem::boundingRect() const
{
    return { -25., -25., 50., 50. };
}

void CharacterGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::green);
    painter->drawEllipse(-25, -25, 50, 50);
    QString d;
    switch (character_->moveData.direction) {
        case Direction::Upward: d = "Up"; break;
        case Direction::Right: d = "Right"; break;
        case Direction::Downward: d = "Down"; break;
        case Direction::Left: d = "Left"; break;
    }
    painter->drawText(-20, 0, d);
    QString l = QString::number(character_->moveData.coordinates.x());
    l += ", ";
    l += QString::number(character_->moveData.coordinates.y());
    painter->drawText(-20, 20, l);
}

void CharacterGraphicsItem::setCharacter(const std::shared_ptr<Character> &newCharacter)
{
    character_ = newCharacter;
}

} // namespace gui
} // namespace bm
