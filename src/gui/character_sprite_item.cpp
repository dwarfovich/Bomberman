#include "character_sprite_item.hpp"
#include "game/character.hpp"

namespace bm {
namespace gui {

CharacterSpriteItem::CharacterSpriteItem(const SpriteItemCallbacks *callbacks, const QPixmap &pixmap)
    : SpriteItem { callbacks, pixmap }
{}

void CharacterSpriteItem::updateSprite()
{
    if (currentSpriteRow_ != destroyAnimationRow_) {
        switch (character_->direction()) {
            case Direction::Upward: setCurrentSpriteRow(0); break;
            case Direction::Right: setCurrentSpriteRow(1); break;
            case Direction::Downward: setCurrentSpriteRow(2); break;
            case Direction::Left: setCurrentSpriteRow(3); break;
        }
    }
    updatePixmapFragment();
    update();
}

void CharacterSpriteItem::setCharacter(const std::shared_ptr<Character> &newCharacter)
{
    character_ = newCharacter;
    updateSprite();
}

bool CharacterSpriteItem::hasDestroyAnimation() const
{
    return true;
}

void CharacterSpriteItem::startDestroyAnimation()
{
    setCurrentSpriteRow(destroyAnimationRow_);
    setCurrentFrame(0);
    update();
}

void CharacterSpriteItem::advance(int phase)
{
    if (currentSpriteRow_ == destroyAnimationRow_ && currentFrame_ == framesCount_ - 1) {
        callbacks_->destroyAnimationFinished(this);
    } else {
        SpriteItem::advance(phase);
    }
}

} // namespace gui
} // namespace bm
