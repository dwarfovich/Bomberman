#include "character_sprite_object.hpp"
#include "direction.hpp"

namespace bm {
namespace gui {

CharacterSpriteObject::CharacterSpriteObject(QGraphicsItem *parent) : AnimatedSpriteGraphicsObject { parent }
{}

void CharacterSpriteObject::updateSpriteMapRow()
{
    switch (character_->direction()) {
        case Direction::Upward: currentSpriteRow_ = 1; break;
        case Direction::Right: currentSpriteRow_ = 2; break;
        case Direction::Downward: currentSpriteRow_ = 3; break;
        case Direction::Left: currentSpriteRow_ = 4; break;
    }
    update();
}

void CharacterSpriteObject::setCharacter(const std::shared_ptr<const Character> &newCharacter)
{
    character_ = newCharacter;
}

} // namespace gui
} // namespace bm
