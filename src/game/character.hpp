#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "game_object.hpp"
#include "direction.hpp"
#include "move_data.hpp"

#include <QPoint>
#include <QPointF>

namespace bm {

struct Character : public GameObject
{
    Character(const MoveData& aMoveData = {});
    MoveData moveData;
};

} // namespace bm

#endif // CHARACTER_HPP
