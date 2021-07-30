#ifndef CELL_HPP
#define CELL_HPP

#include "game_object.hpp"
#include "cell_structure.hpp"
#include "collider.hpp"

#include "modifiers/imodifier.hpp"

namespace bm {

struct Cell : public GameObject
{
    ACCEPT_COLLISION;

    CellStructure              structure = CellStructure::Empty;
    bool                       hasBomb   = false;
    std::shared_ptr<IModifier> modifier  = nullptr;
    size_t                     index     = 0;
};

} // namespace bm

#endif // CELL_HPP
