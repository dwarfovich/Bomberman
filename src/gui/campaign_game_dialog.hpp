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

private: // methods
    void greetPlayer(const QString &playerName);
    void setCurrentLevel(size_t currentLevel);

private: // data
    Ui::CampaignGameDialog *            ui_;
    std::shared_ptr<Game>               game_;
    const std::shared_ptr<const Player> player_;
    mutable GameInitializationData      initializationData_;

    // GameCreationDialog interface
public:
    // TODO: remove this method - map can be accessed through game_.
    const std::shared_ptr<Map> &map() const override;

    // GameCreationDialog interface
public:
    void reset() override;
};

} // namespace gui
} // namespace bm
#endif // BM_GUI_CAMPAIGN_GAME_DIALOG_HPP
