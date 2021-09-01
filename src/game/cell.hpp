#ifndef CELL_HPP
#define CELL_HPP

#include "game_object.hpp"
#include "cell_structure.hpp"
#include "collider.hpp"

#include "modifiers/imodifier.hpp"

namespace bm {

class Cell : public GameObject
{
public:
    ACCEPT_COLLISION;

    friend QDataStream& operator<<(QDataStream& stream, const Cell& cell);
    friend QDataStream& operator>>(QDataStream& stream, Cell& cell);

    CellStructure                     structure() const;
    void                              setStructure(CellStructure structure);
    bool                              hasBomb() const;
    void                              setHasBomb(bool hasBomb);
    const std::shared_ptr<IModifier>& modifier() const;
    void                              setModifier(const std::shared_ptr<IModifier>& modifier);
    size_t                            index() const;
    void                              setIndex(size_t index);

private:
    CellStructure              structure_ = CellStructure::Empty;
    bool                       hasBomb_   = false;
    std::shared_ptr<IModifier> modifier_  = nullptr;
    size_t                     index_     = 0;
};

} // namespace bm

#endif // CELL_HPP
