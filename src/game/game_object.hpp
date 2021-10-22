#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "game_object_id.hpp"

#include <unordered_set>

#define ACCEPT_COLLISION                                                            \
    void collideWith(GameObject& other, Collider& collider) override                \
    {                                                                               \
        auto dispatcher = CollisionDispatcher<decltype(*this)> { *this, collider }; \
        other.accept(dispatcher);                                                   \
    }                                                                               \
    void accept(const CollisionDispatcherBase& dispatcher) override { dispatcher.collide(*this); }

namespace bm {
class Collider;
class CollisionDispatcherBase;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void collideWith(GameObject& other, Collider& c);
    virtual void accept(const CollisionDispatcherBase& c);

    object_id_t id() const;

protected: // data
    object_id_t id_;

private:
    static object_id_t                     nextId_;
    static std::unordered_set<object_id_t> releasedIds_;
};

} // namespace bm

#endif // GAMEOBJECT_HPP
