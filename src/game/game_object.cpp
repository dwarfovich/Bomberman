#include "game_object.hpp"
#include "collider.hpp"

namespace bm {

void GameObject::collideWith(GameObject &other, Collider &c)
{}

void GameObject::accept(const CollisionDispatcherBase &dispatcher)
{}

object_id_t GameObject::id() const
{
    return id_;
}

void GameObject::setId(object_id_t newObjectId)
{
    id_ = newObjectId;
}

} // namespace bm
