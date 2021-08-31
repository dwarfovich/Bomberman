#ifndef BM_GUI_EXPLOSIONGRAPHICSOBJECT_HPP
#define BM_GUI_EXPLOSIONGRAPHICSOBJECT_HPP

#include "animated_sprite_graphics_object.hpp"

namespace bm {
class Explosion;

namespace gui {

enum class ExplosionPart : uint8_t
{
    Center,
    Horizontal,
    Vertical,
    LeftHorizontalEnd,
    RightHorizontalEnd,
    TopVerticalEnd,
    BottomVerticalEnd,
};

class ExplosionGraphicsObject : public AnimatedSpriteGraphicsObject
{
    Q_OBJECT

public:
    explicit ExplosionGraphicsObject(AnimatedSpriteGraphicsObject *parent    = nullptr,
                                     const Explosion *             explosion = nullptr);

    void setExplosionPart(ExplosionPart newExplosionPart);

private:
    ExplosionPart                          explosionPart_ = ExplosionPart::Center;
    std::vector<ExplosionGraphicsObject *> parts_;

    // SpriteGraphicsObject interface
public:
    void                                          setPixmap(const QPixmap &pixmap) override;
    const std::vector<ExplosionGraphicsObject *> &parts() const;
    void                                          setParts(const std::vector<ExplosionGraphicsObject *> &newParts);
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_EXPLOSIONGRAPHICSOBJECT_HPP
