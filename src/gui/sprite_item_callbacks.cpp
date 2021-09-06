#include "sprite_item_callbacks.hpp"
#include "game_scene.hpp"

namespace bm {
namespace gui {

SpriteItemCallbacks::SpriteItemCallbacks(GameScene *scene)
    : destroyAnimationFinished { std::bind(&GameScene::destroyAnimationFinished, scene, std::placeholders::_1) }
    , animationFinished { std::bind(&GameScene::animationFinished, scene, std::placeholders::_1) }
{}

} // namespace gui
} // namespace bm
