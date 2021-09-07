#ifndef BM_SERVERGAME_HPP
#define BM_SERVERGAME_HPP

#include "game.hpp"

#include <vector>

namespace bm {

class ServerGame : public Game
{
    Q_OBJECT

public:
    void                              movePlayer(object_id_t player, Direction direction) override;
    void                              stopPlayer(object_id_t player) override;
    std::shared_ptr<Bomb>             placeBomb(object_id_t player) override;
    object_id_t                       playerId() const override;
    const std::shared_ptr<Bomberman>& bomberman(object_id_t playerId) const override;
};

} // namespace bm

#endif // BM_SERVERGAME_HPP
