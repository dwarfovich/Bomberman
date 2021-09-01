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

class Game : public QObject
{
    Q_OBJECT

    friend class Collider;

public:
    explicit Game(QObject* parent = nullptr);
    virtual ~Game() = default;

    virtual void start() = 0;

    virtual void                              addPlayer(const std::shared_ptr<Bomberman>& player) = 0;
    virtual void                              movePlayer(size_t player, Direction)                = 0;
    virtual void                              stopPlayer(size_t player)                           = 0;
    virtual std::shared_ptr<Bomb>             placeBomb(size_t player)                            = 0;
    virtual const std::shared_ptr<Bomberman>& bomberman(uint8_t playerId) const                   = 0;

    virtual void    setMap(const std::shared_ptr<Map>& map);
    virtual Map*    map() const { return map_.get(); }
    virtual uint8_t playerId() const = 0;

    void setPlayer1Bomberman(const std::shared_ptr<Bomberman>& player);
    bool movePlayer1(Direction direction);
    void stopPlayer1(Direction direction);
    void placeBomb1();
    void setScene(gui::GameScene* newScene);

    void setPlayerBomberman(const std::shared_ptr<Bomberman>& newPlayerBomberman);

signals:
    void gameOver(const bm::GameResult& result);
    void cellChanged(size_t index);
    void objectMoved(const std::shared_ptr<MovingObject>& object);
    void characterStartedMoving(const std::shared_ptr<Character>& character);
    void characterStopped(const std::shared_ptr<Character>& character);
    void bombPlaced(const std::shared_ptr<Bomb>& bomb);
    void bombExploded(const std::shared_ptr<Bomb>& bomb);
    void explosionHappened(const std::shared_ptr<Explosion>& explosion);
    void explosionFinished(const std::shared_ptr<Explosion>& explosion);
    void objectDestroyed(const std::shared_ptr<GameObject>& object);

private slots:
    void onObjectIndexChanged(const std::shared_ptr<MovingObject>& object, size_t index);

protected: // methods
    void addExplosionEvent(const std::shared_ptr<Bomb>& bomb);
    void explodeBomb(const std::shared_ptr<Bomb>& bomb);
    void onExplosionFinished(const std::shared_ptr<Explosion>& explosion);
    //    void objectDestroyed(const std::shared_ptr<GameObject>& object);

protected: // data
    std::shared_ptr<Map> map_;

private: // data
    static const int           timeout_ = 42;
    gui::GameScene*            scene_   = nullptr;
    std::shared_ptr<Bomberman> player1_ = nullptr;
    Collider                   collider_;
    // QTimer                     moveTimer;
    TimerQueue timerQueue;

protected:
    std::shared_ptr<Bomberman> playerBomberman_ = nullptr;
};

} // namespace bm

#endif // GAME_HPP
