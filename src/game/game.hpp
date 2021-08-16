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

    virtual void addPlayer(const std::shared_ptr<Bomberman>& player) = 0;
    virtual void movePlayer(size_t player, Direction)                = 0;
    virtual void stopPlayer(size_t player)                           = 0;
    virtual void placeBomb(size_t player)                            = 0;

    virtual void setMap(const std::shared_ptr<Map>& map);
    virtual Map* map() const { return map_.get(); }

    void setPlayer1Bomberman(const std::shared_ptr<Bomberman>& player);
    bool movePlayer1(Direction direction);
    void stopPlayer1(Direction direction);
    void placeBomb1();
    void setScene(gui::GameScene* newScene);

signals:
    void gameOver(const bm::GameResult& result);

private slots:
    void onObjectIndexChanged(const std::shared_ptr<MovingObject>& object, size_t index);

private: // methods
    void addExplosionEvent(const std::shared_ptr<Bomb>& bomb);
    void explodeBomb(const std::shared_ptr<Bomb>& bomb);

protected: // data
    std::shared_ptr<Map> map_;

private: // data
    static const int           timeout_ = 42;
    gui::GameScene*            scene_   = nullptr;
    std::shared_ptr<Bomberman> player1_ = nullptr;
    Collider                   collider_;
    QTimer                     moveTimer;
    TimerQueue                 timerQueue;
};

} // namespace bm

#endif // GAME_HPP
