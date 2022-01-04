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
    if (cell.structure() == CellStructure::Bricks) {
        const auto &map = game_->map();
        if (cell.index() == map->exitIndex()) {
            emit game_->exitRevealed(cell.index());
        } else {
            map->setModifier(cell.index(), modifierCreator_.chooseModifier());
        }
        map->setCellType(cell.index(), CellStructure::Empty);
    }
}

void Collider::collide(Explosion &explosion, Bomberman &bomberman) const
{
    const auto &bombermanPtr = game_->map()->character(bomberman.id());
    if (bombermanPtr) {
        game_->map()->destroyCharacter(bomberman.id(), explosion.bombOwner());
    }
}

void Collider::collide(Cell &explosion, Bot &bot) const
{}

void Collider::collide(Explosion &explosion, Bot &bot) const
{
    const auto &botPtr = game_->map()->character(bot.id());
    if (botPtr) {
        // emit game_->objectDestroyed(botPtr);
        game_->map()->destroyCharacter(bot.id(), explosion.bombOwner());
    }
}

} // namespace bm
