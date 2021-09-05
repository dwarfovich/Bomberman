#ifndef BM_GUI_CHARACTERSPRITEITEM_HPP
#define BM_GUI_CHARACTERSPRITEITEM_HPP

#include "sprite_item.hpp"

#include <memory>

namespace bm {
class Character;

namespace gui {

class CharacterSpriteItem : public SpriteItem
{
public:
    CharacterSpriteItem(const SpriteItemCallbacks* callbacks = nullptr, const QPixmap& pixmap = {});

    void advance(int phase) override;
    void updateSprite() override;
    bool hasDestroyAnimation() const override;
    void startDestroyAnimation() override;

    void setCharacter(const std::shared_ptr<Character>& newCharacter);

private:
    std::shared_ptr<Character> character_           = nullptr;
    static const int           destroyAnimationRow_ = 4;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_CHARACTERSPRITEITEM_HPP
