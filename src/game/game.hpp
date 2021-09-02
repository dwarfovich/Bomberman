#ifndef GAME_HPP
#define GAME_HPP

#include "map.hpp"
#include "timer_queue.hpp"
#include "collider.hpp"
#include "game_result.hpp"

#include <QTimer>

#include <memory>

namespace bm {
namespace gui {
class GameScene;
}

namespace game_ns {
inline constexpr int movementUpdatePeriod = 42;
}

class Game : public QObject
{
    Q_OBJECT

    friend class Collider;

public:
    Game();
    virtual ~Game() = default;

    virtual void start() = 0;

    virtual void                              setMap(const std::shared_ptr<Map>& map);
    virtual Map*                              map() const;
    virtual void                              movePlayer(object_id_t player, Direction) = 0;
    virtual void                              stopPlayer(object_id_t player)            = 0;
    virtual std::shared_ptr<Bomb>             placeBomb(object_id_t player)             = 0;
    virtual const std::shared_ptr<Bomberman>& bomberman(object_id_t playerId) const     = 0;
    virtual object_id_t                       playerId() const                          = 0;

    object_id_t getPlayerBomberman() const;
    void        setPlayerBomberman(object_id_t playerBomberman);

signals:
    void gameOver(const bm::GameResult& result);
    void cellChanged(size_t index);
    void characterMoved(const std::shared_ptr<Character>& object);
    void characterStartedMoving(const std::shared_ptr<Character>& character);
    void characterStopped(const std::shared_ptr<Character>& character);
    void bombPlaced(const std::shared_ptr<Bomb>& bomb);
    void bombExploded(const std::shared_ptr<Bomb>& bomb);
    void explosionHappened(const std::shared_ptr<Explosion>& explosion);
    void explosionFinished(const std::shared_ptr<Explosion>& explosion);
    void objectDestroyed(const std::shared_ptr<GameObject>& object);

private slots:
    void onObjectsCollided(const Map::Collisions& collisions);
    //    void onCharacterIndexChanged(const std::shared_ptr<Character>& object, size_t index);

protected: // methods
           //    void addExplosionEvent(const std::shared_ptr<Bomb>& bomb);
    //    void explodeBomb(const std::shared_ptr<Bomb>& bomb);
    void onExplosionFinished(const std::shared_ptr<Explosion>& explosion);

protected: // data
    std::shared_ptr<Map> map_;
    object_id_t          playerBomberman_ = 0;
    // std::shared_ptr<Bomberman> playerBomberman_ = nullptr;
    Collider   collider_;
    TimerQueue timerQueue;
    QTimer     movementTimer_;
};

} // namespace bm

#endif // GAME_HPP
