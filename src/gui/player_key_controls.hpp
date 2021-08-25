#ifndef BM_GUI_PLAYERKEYCONTROLS_HPP
#define BM_GUI_PLAYERKEYCONTROLS_HPP

#include <Qt>

namespace bm {
namespace gui {

struct PlayerKeyControls
{
    int moveUp    = Qt::Key_W;
    int moveRight = Qt::Key_D;
    int moveDown  = Qt::Key_S;
    int moveLeft  = Qt::Key_A;
    int placeBomb = Qt::Key_Space;
    int playerId  = 0;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_PLAYERKEYCONTROLS_HPP
