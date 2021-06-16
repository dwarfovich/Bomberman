#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include "map.hpp"

#include <memory>

namespace bm {
class GameLoop {
public:
    void start();

    void setMap(const std::shared_ptr<Map>& map);

    bool movePlayer(Direction direction);

private:
    std::shared_ptr<Map> map_;
};
}  // namespace bm

#endif // GAMELOOP_HPP
