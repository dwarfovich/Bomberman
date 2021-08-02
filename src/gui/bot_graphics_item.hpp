#ifndef BM_GUI_BOTGRAPHICSITEM_HPP
#define BM_GUI_BOTGRAPHICSITEM_HPP

#include "character_graphics_item.hpp"

namespace bm {
namespace gui {

class BotGraphicsItem : public CharacterGraphicsItem
{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_BOTGRAPHICSITEM_HPP
