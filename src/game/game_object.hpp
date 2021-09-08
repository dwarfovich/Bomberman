#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <cinttypes>
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

using object_id_t                      = uint16_t;
inline constexpr object_id_t invalidId = -1;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    virtual void collideWith(GameObject& other, Collider& c);
    virtual void accept(const CollisionDispatcherBase& c);

    object_id_t id() const;

protected: // methods
           // void setId(object_id_t newObjectId);
protected: // data
    object_id_t id_;

private:
    static object_id_t                     nextId_;
    static std::unordered_set<object_id_t> releasedIds_;
};

} // namespace bm

#endif // GAMEOBJECT_HPP
