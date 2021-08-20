#ifndef BM_SERVERGAME_HPP
#define BM_SERVERGAME_HPP

#include "game.hpp"

#include <vector>

namespace bm {

class ServerGame : public Game
{
    Q_OBJECT

public:
    explicit ServerGame(QObject* parent = nullptr);

    void start() override;
    void movePlayer(size_t player, Direction direction) override;
    void stopPlayer(size_t player) override;
    void placeBomb(size_t player) override;
    void addPlayer(const std::shared_ptr<Bomberman>& player) override;
    void setMap(const std::shared_ptr<Map>& map) override;

    bool                              isCorrectPlayerIndex(size_t index) const;
    const std::shared_ptr<Bomberman>& bomberman(uint8_t playerId) const;

protected slots:
    void onObjectIndexChanged(const std::shared_ptr<MovingObject>& object, size_t index);

protected: // methods
    void addExplosionEvent(const std::shared_ptr<Bomb>& bomb);
    void explodeBomb(const std::shared_ptr<Bomb>& bomb);

protected: // data
    static const int                        updateTimeout_ = 42;
    std::vector<std::shared_ptr<Bomberman>> bombermans_;
    Collider                                collider_;
    QTimer                                  moveTimer;
    TimerQueue                              timerQueue;
};

} // namespace bm

#endif // BM_SERVERGAME_HPP
