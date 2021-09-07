#include "game_object.hpp"
#include "collider.hpp"

namespace bm {

object_id_t                     GameObject::nextId_      = 0;
std::unordered_set<object_id_t> GameObject::releasedIds_ = {};

GameObject::GameObject()
{
    if (releasedIds_.empty()) {
        id_ = nextId_++;
    } else {
        id_ = *releasedIds_.cbegin();
        releasedIds_.erase(releasedIds_.begin());
    }
}

GameObject::~GameObject()
{
    releasedIds_.insert(id_);
}

void GameObject::collideWith(GameObject &other, Collider &c)
{}

void GameObject::accept(const CollisionDispatcherBase &dispatcher)
{}

object_id_t GameObject::id() const
{
    return id_;
}

// void GameObject::setId(object_id_t newObjectId)
//{
////    releasedIds_.insert(id_);
////    id_ = newObjectId;
//}

} // namespace bm
