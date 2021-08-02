#ifndef CHARACTERGRAPHICSITEM_HPP
#define CHARACTERGRAPHICSITEM_HPP

//#include "game/character.hpp"
#include "game/moving_object.hpp"

#include <QGraphicsItem>

#include <memory>

namespace bm {
namespace gui {

class CharacterGraphicsItem : public QGraphicsItem
{
public:
    CharacterGraphicsItem();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void   paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setCharacter(const std::shared_ptr<MovingObject> &newCharacter);

protected:
    std::shared_ptr<MovingObject> character_;
};

} // namespace gui
} // namespace bm

#endif // CHARACTERGRAPHICSITEM_HPP
