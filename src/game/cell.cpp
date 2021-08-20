#include "cell.hpp"
#include "modifiers/modifier_factory.hpp"

namespace bm {

QDataStream& operator<<(QDataStream& stream, const Cell& cell)
{
    stream << cell.structure_;
    stream << cell.hasBomb_;
    if (cell.modifier_) {
        stream << cell.modifier_->type();
    } else {
        stream << ModifierType::Dummy;
    }

    return stream;
}

QDataStream& operator>>(QDataStream& stream, Cell& cell)
{
    stream >> cell.structure_;
    stream >> cell.hasBomb_;
    ModifierType modifierType;
    stream >> modifierType;
    ModifierFactory factory;
    cell.modifier_ = factory.createModifier(modifierType);

    return stream;
}

CellStructure Cell::structure() const
{
    return structure_;
}

void Cell::setStructure(CellStructure newStructure)
{
    structure_ = newStructure;
}

bool Cell::hasBomb() const
{
    return hasBomb_;
}

void Cell::setHasBomb(bool hasBomb)
{
    hasBomb_ = hasBomb;
}

const std::shared_ptr<IModifier>& Cell::modifier() const
{
    return modifier_;
}

void Cell::setModifier(const std::shared_ptr<IModifier>& newModifier)
{
    modifier_ = newModifier;
}

size_t Cell::index() const
{
    return index_;
}

void Cell::setIndex(size_t newIndex)
{
    index_ = newIndex;
}

} // namespace bm
