#ifndef GAMEVIEW_HPP
#define GAMEVIEW_HPP

#include "game/map.hpp"
#include "game_scene.hpp"

#include <QGraphicsView>

#include <memory>

namespace bm {
namespace gui {

class GameView : public QGraphicsView
{
public:
    explicit GameView(QWidget* parent = nullptr);

    void setMap(const std::shared_ptr<Map>& map);

    GameScene* scene() const;

private:
    GameScene*           scene_;
    std::shared_ptr<Map> map_;
};

} // namespace gui
} // namespace bm

#endif // GAMEVIEW_HPP
