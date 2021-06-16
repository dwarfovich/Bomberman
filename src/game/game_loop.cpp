#include "game_loop.hpp"

namespace bm {
void GameLoop::start()
{
}

void GameLoop::setMap(const std::shared_ptr<Map>& map)
{
    map_ = map;
}

bool GameLoop::movePlayer(Direction direction)
{
    const auto& player = map_->player();

    if (map_->canMoveCharacter(*player, direction)) {
        map_->moveCharacter(*player, direction);
        return (true);
    }
    else {
        return (false);
    }
}
}  // namespace bm
