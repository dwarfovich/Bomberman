#include "explosion_processor.hpp"

#include "game_object.hpp"
#include "cell.hpp"
#include "bomberman.hpp"
#include "map.hpp"
#include "game.hpp"

#include <QDebug>

namespace bm {

ExplosionProcessor::ExplosionProcessor(Game &game) : game_ { game }
{}

void ExplosionProcessor::setBomb(const std::shared_ptr<Bomb> &bomb)
{
    bomb_ = bomb;
}

void ExplosionProcessor::explode(GameObject &object)
{
    qDebug() << "Explode unknown object";
}

void ExplosionProcessor::explode(Cell &cell)
{
    if (cell.structure == CellStructure::Bricks) {
        game_.map_->setCellType(cell.index, CellStructure::Empty);
        game_.map_->setModifier(cell.index, modifierCreator_.chooseModifier());
    }
}

void ExplosionProcessor::explode(Bomberman &bomberman)
{
    qDebug() << "Explode bomberman";
}

} // namespace bm
