#include "game_object.hpp"
#include "collider.hpp"

namespace bm {

void GameObject::collideWith(GameObject &other, Collider &c)
{}

void GameObject::accept(const CollisionDispatcherBase &dispatcher)
{}

} // namespace bm
