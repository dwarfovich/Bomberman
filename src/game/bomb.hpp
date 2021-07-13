#ifndef BOMB_HPP
#define BOMB_HPP

#include "time.hpp"

#include <memory>

namespace bm {
class Bomberman;

struct Bomb
{
    std::shared_ptr<Bomberman> owner     = nullptr;
    int                        radius    = 0;
    size_t                     cellIndex = 0;
//    using namespace std::literals;
    Milliseconds explosionDelay {1000};
};

} // namespace bm

#endif // BOMB_HPP
