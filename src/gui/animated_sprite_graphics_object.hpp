#ifndef BM_GUI_ANIMATEDSPRITEGRAPHICSOBJECT_HPP
#define BM_GUI_ANIMATEDSPRITEGRAPHICSOBJECT_HPP

#include "sprite_graphics_object.hpp"

namespace bm {
namespace gui {

class AnimatedSpriteGraphicsObject : public SpriteGraphicsObject
{
    Q_OBJECT

public:
    explicit AnimatedSpriteGraphicsObject(QGraphicsItem* parent = nullptr);

    bool isAnimated() const override;
    void setCurrentFrame(int frame) override;

protected:
    int currentSpriteRow_ = 0;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_ANIMATEDSPRITEGRAPHICSOBJECT_HPP
