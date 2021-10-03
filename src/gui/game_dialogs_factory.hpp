#ifndef BM_GUI_GAMEDIALOGSFACTORY_HPP
#define BM_GUI_GAMEDIALOGSFACTORY_HPP

#include "game/game_type.hpp"
#include "game_dialogs.hpp"

#include <Qt>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

namespace bm {
namespace gui {

GameDialogs createGamesDialog(QWidget* parentWidget, GameType type);

} // namespace gui
} // namespace bm

#endif // BM_GUI_GAMEDIALOGSFACTORY_HPP
