#ifndef BM_COLLIDER_HPP
#define BM_COLLIDER_HPP

#include "modifiers/modifier_creator.hpp"

#include <QDebug>

#include <iostream>

#define COLLIDE_WITH(TYPE) \
    void collide(TYPE& object) const override { collider_.collide(first_, object); }

#define ADD_INVERSE_COLLISION(TYPE1, TYPE2) \
    void collide(TYPE2& lhs, TYPE1& rhs) const { collide(rhs, lhs); }

namespace bm {
class Game;
class GameObject;
class Explosion;
class Cell;
class Bomberman;
class Bot;

class Collider
{
public:
    Collider(Game* game = nullptr);

    void collide(Explosion& explosion, GameObject& object) const;
    void collide(Explosion& explosion, Cell& cell) const;
    ADD_INVERSE_COLLISION(Explosion, Cell);
    void collide(Explosion& explosion, Bomberman&) const { qDebug() << "Exploding bomberman\n"; }
    ADD_INVERSE_COLLISION(Explosion, Bomberman);
    void collide(Explosion& explosion, Bot& bot) const;
    ADD_INVERSE_COLLISION(Explosion, Bot);

    void collide(Cell& lhs, GameObject& rhs) const { std::cout << "(Cell, GameObject\n"; }
    void collide(Cell& lhs, Bomberman& rhs) const { std::cout << "(Cell, GameObject\n"; }
    ADD_INVERSE_COLLISION(Cell, Bomberman);
    void collide(Cell& explosion, Bot&) const;
    ADD_INVERSE_COLLISION(Cell, Bot);

    void collide(Bomberman& lhs, GameObject& rhs) const { std::cout << "(Bomberman, GameObject\n"; }

    void collide(Bot& explosion, Bomberman&) const { qDebug() << "Exploding bot\n"; }
    ADD_INVERSE_COLLISION(Bot, Bomberman);
    void collide(Bot& explosion, GameObject&) const { qDebug() << "Exploding bot\n"; }

private:
    Game*           game_ = nullptr;
    ModifierCreator modifierCreator_;
};

class CollisionDispatcherBase
{
public:
    virtual ~CollisionDispatcherBase() = default;

    virtual void collide(Explosion& explosion) const = 0;
    virtual void collide(Cell& cell) const           = 0;
    virtual void collide(Bomberman& cell) const      = 0;
    virtual void collide(Bot& cell) const            = 0;
};

template<class Type>
class CollisionDispatcher : public CollisionDispatcherBase
{
public:
    CollisionDispatcher(Type& first, Collider& collider) : first_ { first }, collider_ { collider } {};

    COLLIDE_WITH(Explosion);
    COLLIDE_WITH(Cell);
    COLLIDE_WITH(Bomberman);
    COLLIDE_WITH(Bot);

private:
    Type&           first_;
    const Collider& collider_;
};

} // namespace bm

#endif // BM_COLLIDER_HPP
