#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "explosion_processor.hpp"

#ifndef ALLOW_EXPLOSION_VISITOR
    #define ALLOW_EXPLOSION_VISITOR \
        void explode(ExplosionProcessor& processor) override { processor.explode(*this); }
#endif

namespace bm {
class ExplosionProcessor;

class GameObject
{
public:
    virtual ~GameObject() = default;
    virtual void explode(ExplosionProcessor& processor);
};

} // namespace bm

#endif // GAMEOBJECT_HPP
