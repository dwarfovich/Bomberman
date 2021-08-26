#ifndef BM_GUI_CHARACTERSPRITEOBJECT_HPP
#define BM_GUI_CHARACTERSPRITEOBJECT_HPP

#include "animated_sprite_graphics_object.hpp"
#include "game/character.hpp"

namespace bm {
namespace gui {

class CharacterSpriteObject : public AnimatedSpriteGraphicsObject
{
public:
    explicit CharacterSpriteObject(QGraphicsItem* parent = nullptr);

    void updateSpriteMapRow() override;

    void setCharacter(const std::shared_ptr<const Character>& newCharacter);

private:
    std::shared_ptr<const Character> character_ = nullptr;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_CHARACTERSPRITEOBJECT_HPP
