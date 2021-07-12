#ifndef CHARACTERGRAPHICSITEM_HPP
#define CHARACTERGRAPHICSITEM_HPP

#include "game/character.hpp"

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

    void setCharacter(const std::shared_ptr<Character> &newCharacter);

private:
    std::shared_ptr<Character> character_;
};

} // namespace gui
} // namespace bm

#endif // CHARACTERGRAPHICSITEM_HPP
