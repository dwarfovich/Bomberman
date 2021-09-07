#ifndef CELLSTRUCTURE_HPP
#define CELLSTRUCTURE_HPP

#include <cinttypes>

namespace bm {

enum class CellStructure : uint8_t
{
    Empty = 0,
    Concrete,
    Bricks,
    EndValue
};

} // namespace bm

#endif // CELLSTRUCTURE_HPP
