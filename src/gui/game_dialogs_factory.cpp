#include "game_dialogs_factory.hpp"
#include "fast_game_creation_dialog.hpp"
#include "fast_game_over_dialog.hpp"
#include "campaign_game_dialog.hpp"

namespace bm {
namespace gui {

GameDialogs createGamesDialog(QWidget* parentWidget, GameType type, const std::shared_ptr<Player>& player)
{
    GameDialogs dialogs { parentWidget };
    switch (type) {
        case GameType::Fast:
            dialogs.creationDialog = new FastGameCreationDialog { parentWidget, player };
            dialogs.gameOverDialog = new FastGameOverDialog { parentWidget };
            break;

        case GameType::Campaign:
            dialogs.creationDialog = new CampaignGameDialog { player, parentWidget };
            dialogs.gameOverDialog = new FastGameOverDialog { parentWidget };
            break;
    }

    return dialogs;
}

} // namespace gui
} // namespace bm
