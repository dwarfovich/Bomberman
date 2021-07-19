#ifndef GAME_HPP
#define GAME_HPP

#include "map.hpp"
#include "timer_queue.hpp"
#include "explosion_processor.hpp"

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

public:
    Game();

    void start();

    void       setMap(const std::shared_ptr<Map>& map);
    const Map& map() const { return *map_; }

    bool movePlayer(Direction direction);
    void stopPlayer(Direction direction);
    void placeBomb();

    void setScene(gui::GameScene* newScene);

private slots:
    void onBombermanIndexChanged(const std::shared_ptr<Bomberman>& bomberman, size_t index);

private: // methods
    void addExplosionEvent(const std::shared_ptr<Bomb>& bomb);
    void explodeBomb(const std::shared_ptr<Bomb>& bomb);

private: // data
    static const int     timeout_ = 42;
    std::shared_ptr<Map> map_;
    gui::GameScene*      scene_ = nullptr;
    ExplosionProcessor   explosionProcessor;
    QTimer               moveTimer;
    TimerQueue           timerQueue;
};
} // namespace bm

#endif // GAME_HPP
