#include "game_creation_dialog.hpp"

namespace bm {
namespace gui {

GameCreationDialog::GameCreationDialog(QWidget *parent, const std::shared_ptr<Player> &player)
    : QDialog { parent }, player_ { player }
{}

void GameCreationDialog::updateScreen()
{}

const std::shared_ptr<Map> &GameCreationDialog::map() const
{
    static const std::shared_ptr<Map> empty;
    return empty;
}

const std::shared_ptr<Player> &GameCreationDialog::player() const
{
    return player_;
}

void GameCreationDialog::setPlayer(const std::shared_ptr<Player> &newPlayer)
{
    player_ = newPlayer;
}

} // namespace gui
} // namespace bm
