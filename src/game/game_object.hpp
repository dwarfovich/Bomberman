#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

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
    virtual ~GameObject() = default;

    virtual void collideWith(GameObject& other, Collider& c);
    virtual void accept(const CollisionDispatcherBase& c);
};

} // namespace bm

#endif // GAMEOBJECT_HPP
