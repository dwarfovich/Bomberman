#ifndef GAME_HPP
#define GAME_HPP

#include "map.hpp"
#include "timer_queue.hpp"
#include "collider.hpp"
#include "game_result.hpp"
#include "game_status.hpp"
#include "game_process_handler.hpp"

#include <QTimer>

#include <memory>

namespace bm {
class GameProcessHandler;
class Player;

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
    friend class GameProcessHandler;

public:
    Game();
    virtual ~Game() = default;

    virtual void                  movePlayer(object_id_t player, Direction) = 0;
    virtual void                  stopPlayer(object_id_t player)            = 0;
    virtual std::shared_ptr<Bomb> placeBomb(object_id_t player)             = 0;

    virtual object_id_t                       playerId() const;
    virtual const std::shared_ptr<Bomberman>& bomberman(object_id_t playerId) const;
    virtual void                              start();

    virtual void                        setMap(const std::shared_ptr<Map>& map);
    virtual const std::shared_ptr<Map>& map() const;

    virtual void setGameProcessHandler(std::unique_ptr<GameProcessHandler> handler);

    object_id_t getPlayerBomberman() const;
    void        setPlayerBomberman(object_id_t playerBomberman);

    GameStatus currentStatus() const;

    const GameResult& gameResult() const;

    void addPlayer(const std::shared_ptr<Player>& player);

signals:
    void gameOver();
    void cellStructureChanged(size_t index, CellStructure previousStructure);
    void characterMoved(const std::shared_ptr<Character>& object);
    void characterStartedMoving(const std::shared_ptr<Character>& character);
    void characterStopped(const std::shared_ptr<Character>& character);
    void bombPlaced(const std::shared_ptr<Bomb>& bomb);
    void bombExploded(const std::shared_ptr<Bomb>& bomb);
    void explosionHappened(const std::shared_ptr<Explosion>& explosion);
    void explosionFinished(const std::shared_ptr<Explosion>& explosion);
    void characterDestroyed(const std::shared_ptr<Character>& victim, const std::shared_ptr<Character>& killer);
    void objectDestroyed(const std::shared_ptr<GameObject>& object);
    void modifierAdded(size_t index, const std::shared_ptr<IModifier>& modifier);
    void modifierRemoved(size_t index, const std::shared_ptr<IModifier>& modifier);
    void exitRevealed(size_t index);
    void exitActivated();
    void gameStatusChanged(bm::GameStatus newStatus);

private slots:
    void onObjectsCollided(const Map::Collisions& collisions);
    void onCharacterIndexChanged(const std::shared_ptr<Character>& object, size_t index);

protected: // methods
    virtual void prepareToStart();
    virtual void addExplosionEvent(const std::shared_ptr<Bomb>& bomb);
    virtual void explodeBomb(const std::shared_ptr<Bomb>& bomb);
    virtual void onExplosionFinished(const std::shared_ptr<Explosion>& explosion);

    virtual void setGameStatus(GameStatus status);

protected: // data
    std::shared_ptr<Map>                 map_;
    std::unique_ptr<GameProcessHandler>  gameProcessHandler_;
    std::vector<std::shared_ptr<Player>> players_;
    object_id_t                          playerId_ = invalidObjectId;
    Collider                             collider_;
    TimerQueue                           timerEventsQueue;
    QTimer                               movementTimer_;
    GameStatus                           currentStatus_ = GameStatus::Waiting;
    GameResult                           gameResult_;
};

} // namespace bm

#endif // GAME_HPP
