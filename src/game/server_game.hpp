#ifndef BM_SERVERGAME_HPP
#define BM_SERVERGAME_HPP

#include "game.hpp"

#include <vector>

namespace bm {

class ServerGame : public Game
{
    Q_OBJECT

public:
    void                  setMap(const std::shared_ptr<Map>& map) override;
    void                  start() override;
    void                  movePlayer(object_id_t player, Direction direction) override;
    void                  stopPlayer(object_id_t player) override;
    std::shared_ptr<Bomb> placeBomb(object_id_t player) override;
    object_id_t           playerId() const override;

    //    bool                              isCorrectPlayerIndex(size_t index) const;
    const std::shared_ptr<Bomberman>& bomberman(object_id_t playerId) const override;

protected slots:
    void onCharacterIndexChanged(const std::shared_ptr<Character>& character, size_t index);

protected: // methods
    void addExplosionEvent(const std::shared_ptr<Bomb>& bomb);
    void explodeBomb(const std::shared_ptr<Bomb>& bomb);
};

} // namespace bm

#endif // BM_SERVERGAME_HPP
