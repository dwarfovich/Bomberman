#ifndef CELL_HPP
#define CELL_HPP

#include "cell_type.hpp"
#include "modifiers/modifier_type.hpp"

namespace bm {
struct Cell {
    CellType type = CellType::Empty;
    //game::ModifierType modifier = game::ModifierType::Dummy;
    bool hasBomb = false;
};
}  // namespace bm

#endif  // CELL_HPP
