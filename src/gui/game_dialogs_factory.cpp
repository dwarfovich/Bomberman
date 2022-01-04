#include "game_dialogs_factory.hpp"
#include "fast_game_creation_dialog.hpp"
#include "fast_game_over_dialog.hpp"
#include "campaign_game_dialog.hpp"
#include "campaign_game_over_dialog.hpp"
#include "create_network_game_dialog.hpp"
#include "network_game_over_dialog.hpp"
#include "client_game_dialog.hpp"
#include "game/player.hpp"

namespace bm {
namespace gui {

GameDialogs createGameDialogs(QWidget* parentWidget, GameType type, const std::shared_ptr<Player>& player)
{
    GameDialogs dialogs { parentWidget };
    switch (type) {
            // TODO: unify constructors of creation and game over dialogs.
        case GameType::Fast:
            dialogs.creationDialog = new FastGameCreationDialog { parentWidget, player };
            dialogs.gameOverDialog = new FastGameOverDialog { player, parentWidget };
            break;

        case GameType::Campaign:
            dialogs.creationDialog = new CampaignGameDialog { player, parentWidget };
            dialogs.gameOverDialog = new CampaignGameOverDialog { player, parentWidget };
            break;

        case GameType::Server:
            dialogs.creationDialog = new CreateNetworkGameDialog { player, parentWidget };
            dialogs.gameOverDialog = new NetworkGameOverDialog { player, parentWidget };
            break;

        case GameType::Client:
            dialogs.creationDialog = new ClientGameDialog { player, parentWidget };
            dialogs.gameOverDialog = new NetworkGameOverDialog { player, parentWidget };
            break;

        default: Q_ASSERT(false);
    }

    return dialogs;
}

} // namespace gui
} // namespace bm
