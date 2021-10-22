#ifndef BM_GUI_PLAYERKEYCONTROLS_HPP
#define BM_GUI_PLAYERKEYCONTROLS_HPP

#include "game/game_object_id.hpp"

#include <Qt>

namespace bm {
namespace gui {

class PlayerKeyControls
{
public:
    int         moveUp    = Qt::Key_W;
    int         moveRight = Qt::Key_D;
    int         moveDown  = Qt::Key_S;
    int         moveLeft  = Qt::Key_A;
    int         placeBomb = Qt::Key_Space;
    object_id_t playerId  = invalidObjectId;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_PLAYERKEYCONTROLS_HPP
