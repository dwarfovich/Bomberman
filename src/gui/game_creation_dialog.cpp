#include "game_creation_dialog.hpp"

namespace bm {
namespace gui {

GameCreationDialog::GameCreationDialog(QWidget *parent) : QDialog { parent }
{}

const std::shared_ptr<Map> &GameCreationDialog::map() const
{
    static const std::shared_ptr<Map> empty;
    return empty;
}

} // namespace gui
} // namespace bm
