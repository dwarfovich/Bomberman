#ifndef BM_GUI_SPRITEITEMCALLBACKS_HPP
#define BM_GUI_SPRITEITEMCALLBACKS_HPP

#include <functional>

namespace bm {
namespace gui {
class SpriteItem;
class GameScene;

class SpriteItemCallbacks
{
public:
    SpriteItemCallbacks(GameScene* scene = nullptr);

    std::function<void(SpriteItem*)> destroyAnimationFinished;
    std::function<void(SpriteItem*)> animationFinished;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_SPRITEITEMCALLBACKS_HPP
