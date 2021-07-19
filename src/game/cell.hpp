#ifndef CELL_HPP
#define CELL_HPP

#include "game_object.hpp"
#include "cell_structure.hpp"
#include "modifiers/imodifier.hpp"

namespace bm {

struct Cell : public GameObject
{
    ALLOW_EXPLOSION_VISITOR;

    CellStructure              structure = CellStructure::Empty;
    bool                       hasBomb   = false;
    std::shared_ptr<IModifier> modifier  = nullptr;
    size_t                     index     = 0;
};

} // namespace bm

#endif // CELL_HPP
