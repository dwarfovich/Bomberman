#ifndef BM_GUI_GAMEDIALOGSFACTORY_HPP
#define BM_GUI_GAMEDIALOGSFACTORY_HPP

#include "game/game_type.hpp"
#include "game_dialogs.hpp"

#include <Qt>

#include <memory>

QT_BEGIN_NAMESPACE
class QWidget;
QT_END_NAMESPACE

namespace bm {
class Player;

namespace gui {

GameDialogs createGamesDialog(QWidget* parentWidget, GameType type, const std::shared_ptr<Player>& player);

} // namespace gui
} // namespace bm

#endif // BM_GUI_GAMEDIALOGSFACTORY_HPP
