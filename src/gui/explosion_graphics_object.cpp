#include "explosion_graphics_object.hpp"

#include <QGraphicsScene>

namespace bm {
namespace gui {

ExplosionGraphicsObject::ExplosionGraphicsObject(AnimatedSpriteGraphicsObject *parent, const Explosion *explosion)
    : AnimatedSpriteGraphicsObject { parent }
{}

void ExplosionGraphicsObject::setExplosionPart(ExplosionPart newExplosionPart)
{
    explosionPart_ = newExplosionPart;
    setSpriteRow(static_cast<int>(explosionPart_));
}

const std::vector<ExplosionGraphicsObject *> &ExplosionGraphicsObject::parts() const
{
    return parts_;
}

void ExplosionGraphicsObject::setParts(const std::vector<ExplosionGraphicsObject *> &newParts)
{
    parts_ = newParts;
}

void ExplosionGraphicsObject::setPixmap(const QPixmap &pixmap)
{
    AnimatedSpriteGraphicsObject::setPixmap(pixmap);
    auto children = childItems();
    for (auto *child : children) {
        auto eChild = static_cast<ExplosionGraphicsObject *>(child);
        eChild->setExplosionPart(ExplosionPart::BottomVerticalEnd);
        eChild->setPixmap(pixmap_);
    }
}

} // namespace gui
} // namespace bm
