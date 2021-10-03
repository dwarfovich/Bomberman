#include "game_dialogs_factory.hpp"
#include "fast_game_creation_dialog.hpp"

namespace bm {
namespace gui {

GameDialogs createGamesDialog(QWidget *parentWidget, GameType type)
{
    GameDialogs dialogs { parentWidget };
    switch (type) {
        case GameType::Fast: dialogs.creationDialog = new FastGameCreationDialog { parentWidget }; break;
    }

    return dialogs;
}

} // namespace gui
} // namespace bm
