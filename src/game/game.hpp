#ifndef GAME_HPP
#define GAME_HPP

#include "map.hpp"
#include "timer_queue.hpp"
#include "collider.hpp"

#include <QTimer>

#include <memory>

namespace bm {
namespace gui {
class GameScene;
}

class Game : public QObject
{
    Q_OBJECT

    friend class ExplosionProcessor;
    friend class Collider;

public:
    Game();

    void start();

    void       setMap(const std::shared_ptr<Map>& map);
    Map* map() const { return map_.get(); }

    void setPlayer(const std::shared_ptr<Bomberman>& player);
    bool movePlayer(Direction direction);
    void stopPlayer(Direction direction);
    void placeBomb();

    void setScene(gui::GameScene* newScene);

private slots:
    void onObjectIndexChanged(const std::shared_ptr<MovingObject>& object, size_t index);

private: // methods
    void initializeBots();
    void addExplosionEvent(const std::shared_ptr<Bomb>& bomb);
    void explodeBomb(const std::shared_ptr<Bomb>& bomb);

private: // data
    static const int           timeout_ = 42;
    std::shared_ptr<Map>       map_;
    gui::GameScene*            scene_  = nullptr;
    std::shared_ptr<Bomberman> player_ = nullptr;
    Collider                   collider_;
    QTimer                     moveTimer;
    TimerQueue                 timerQueue;
};

} // namespace bm

#endif // GAME_HPP
