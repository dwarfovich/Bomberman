#include "game_object.hpp"

namespace bm {

void GameObject::explode(ExplosionProcessor &processor)
{
    processor.explode(*this);
}

} // namespace bm
