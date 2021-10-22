#ifndef BM_GUI_CAMPAIGN_GAME_DIALOG_HPP
#define BM_GUI_CAMPAIGN_GAME_DIALOG_HPP

#include "game_creation_dialog.hpp"
#include "game/game_initialization_data.hpp"

#include <memory>

namespace bm {
class Player;
class Game;

namespace gui {

namespace Ui {
class CampaignGameDialog;
}

class CampaignGameDialog : public GameCreationDialog
{
    Q_OBJECT

public:
    explicit CampaignGameDialog(const std::shared_ptr<Player> &player, QWidget *parent = nullptr);
    ~CampaignGameDialog();

    const GameInitializationData &initializationData() const override;

private:
    Ui::CampaignGameDialog *       ui_;
    std::shared_ptr<Game>          game_;
    mutable GameInitializationData initializationData_;

    // GameCreationDialog interface
public:
    const std::shared_ptr<Map> &map() const override;
};

} // namespace gui
} // namespace bm
#endif // BM_GUI_CAMPAIGN_GAME_DIALOG_HPP
