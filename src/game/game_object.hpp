#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <cinttypes>

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

using object_id_t = uint16_t;

class GameObject
{
public:
    virtual ~GameObject() = default;

    virtual void collideWith(GameObject& other, Collider& c);
    virtual void accept(const CollisionDispatcherBase& c);

    object_id_t id() const;
    void        setId(object_id_t newObjectId);

protected:
    object_id_t id_;
};

} // namespace bm

#endif // GAMEOBJECT_HPP
