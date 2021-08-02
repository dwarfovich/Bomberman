#include "collider.hpp"
#include "cell.hpp"
#include "game.hpp"
#include "map.hpp"
#include "gui/game_scene.hpp"

#include <QDebug>

namespace bm {

Collider::Collider(Game *game) : game_ { game }
{}

void Collider::collide(Explosion &explosion, GameObject &object) const
{
    qDebug() << "Colliding explosion and GameObject\n";
}

void Collider::collide(Explosion &explosion, Cell &cell) const
{
    if (cell.structure == CellStructure::Bricks) {
        game_->map_->setCellType(cell.index, CellStructure::Empty);
        game_->map_->setModifier(cell.index, modifierCreator_.chooseModifier());
    }
}

void Collider::collide(Cell &explosion, Bot & bot) const
{
}

void Collider::collide(Explosion &explosion, Bot & bot) const {
    const auto& botPtr = game_->map()->sharedPtrForObject(bot);
    if (botPtr) {
        game_->scene_->destroyItemForObject(botPtr);
        game_->map()->removeMovingObject(botPtr);
    }
}

} // namespace bm
