#ifndef BM_GUI_ANIMATEDSPRITEGRAPHICSOBJECT_HPP
#define BM_GUI_ANIMATEDSPRITEGRAPHICSOBJECT_HPP

#include "sprite_graphics_object.hpp"
#include "game/character.hpp"

namespace bm {
namespace gui {

class AnimatedSpriteGraphicsObject : public SpriteGraphicsObject
{
    Q_OBJECT

public:
    explicit AnimatedSpriteGraphicsObject(QGraphicsItem* parent = nullptr);

    bool isAnimated() const override;
    void setCurrentFrame(int frame) override;
    void advanceFrame();

protected:
    int                        framesCount_               = 10;
    int                        currentSpriteRow_          = 0;
    std::shared_ptr<Character> character_                 = nullptr;
    bool                       animationInProgress        = false;
    int                        destroyAnimationSpriteRow_ = -1;

    // SpriteGraphicsObject interface
public:
    void updateSpriteMapRow() override;
    void setCharacter(const std::shared_ptr<Character>& newCharacter);
    void setSpriteRow(int row);

    // QGraphicsItem interface
public:
    void advance(int phase) override;

    // SpriteGraphicsObject interface
public:
    int  framesCount() const override;
    void setFramesCount(int newFramesCount);

    // SpriteGraphicsObject interface
public:
    void startDestroyAnimation() override;
    int  destroyAnimationSpriteRow() const;
    void setDestroyAnimationSpriteRow(int newDestroyAnimationSpriteRow);
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_ANIMATEDSPRITEGRAPHICSOBJECT_HPP
