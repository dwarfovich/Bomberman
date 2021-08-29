#ifndef BM_GUI_EXPLOSIONGRAPHICSOBJECT_HPP
#define BM_GUI_EXPLOSIONGRAPHICSOBJECT_HPP

#include "animated_sprite_graphics_object.hpp"

namespace bm {
class Explosion;

namespace gui {

class ExplosionGraphicsObject : public AnimatedSpriteGraphicsObject
{
    Q_OBJECT

public:
    explicit ExplosionGraphicsObject(const Explosion* explosion);
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_EXPLOSIONGRAPHICSOBJECT_HPP
