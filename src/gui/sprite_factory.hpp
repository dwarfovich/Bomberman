#ifndef BM_SPRITEFACTORY_HPP
#define BM_SPRITEFACTORY_HPP

#include <QPoint>
#include <QPixmap>

#include <memory>

namespace bm {
class Cell;
class Bomberman;
class Bot;
class Bomb;
class Explosion;
class IModifier;
class Map;

namespace gui {
class SpriteItem;
class CellSpriteItem;
class ExplosionSpriteItem;
class ModifierSpriteItem;
class SpriteItemCallbacks;

class SpriteObjectFactory
{
public:
    SpriteObjectFactory(const SpriteItemCallbacks* const callbacks = nullptr);

    std::unique_ptr<CellSpriteItem>      createSprite(const Cell* cell);
    std::unique_ptr<SpriteItem>          createSprite(const std::shared_ptr<Bomberman>& character);
    std::unique_ptr<SpriteItem>          createSprite(const std::shared_ptr<Bot>& character);
    std::unique_ptr<SpriteItem>          createSprite(const std::shared_ptr<Bomb>& bomb);
    std::unique_ptr<ExplosionSpriteItem> createSprite(const Explosion* explosion,
                                                      const Map&       map,
                                                      const QPoint&    centerCoordinates = {});
    std::unique_ptr<SpriteItem>          createSprite(size_t index, const std::shared_ptr<IModifier>& modifier);
    std::unique_ptr<SpriteItem>          createExitSprite();

    QPoint mapCoordinatesToSceneCoordinates(const QPoint& coordinates) const;

private:
    enum SpriteZValue
    {
        ZCell,
        ZExit,
        ZModifier,
        ZCharacter,
        ZBomb,
        ZExplosion
    };

    const SpriteItemCallbacks* const callbacks_;
    QPixmap                          cell_;
    QPixmap                          bomberman_;
    QPixmap                          bot_;
    QPixmap                          bomb_;
    QPixmap                          explosion_;
    QPixmap                          modifiers_;
    QPixmap                          exit_;
};

} // namespace gui
} // namespace bm

#endif // BM_SPRITEFACTORY_HPP
