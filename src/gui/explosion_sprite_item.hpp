#ifndef BM_GUI_EXPLOSIONSPRITEITEM_HPP
#define BM_GUI_EXPLOSIONSPRITEITEM_HPP

#include "sprite_item.hpp"

#include <QPainter>

#include <vector>

namespace bm {
namespace gui {

class ExplosionSpriteItem : public SpriteItem
{
public:
    enum PartType : uint8_t
    {
        Center,
        Horizontal,
        Vertical,
        LeftHorizontalEnding,
        RightHorizontalEnding,
        TopVerticalEnding,
        BottomVerticalEnding,
    };

    ExplosionSpriteItem(const SpriteItemCallbacks *callbacks = nullptr, const QPixmap &pixmap = {});

    void advance(int phase) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void addExplosionPart(std::unique_ptr<SpriteItem> part);

private:
    std::vector<std::unique_ptr<SpriteItem>> explosionParts_;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_EXPLOSIONSPRITEITEM_HPP
