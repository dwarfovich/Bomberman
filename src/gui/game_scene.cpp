#include "game_scene.hpp"
#include "game/character.hpp"

#include <QKeyEvent>
#include <QDebug>

namespace bm {
namespace gui {

GameScene::GameScene(QObject* parent) : QGraphicsScene { parent }
{}

bool GameScene::setCellItem(CellItem* item, size_t index)
{
    try {
        if (index >= cellItems_.size()) {
            cellItems_.resize(index + 1);
        }
        cellItems_[index] = item;
        addItem(cellItems_[index]);

        return true;
    } catch (...) {
        return false;
    }
}

void GameScene::addCharacter(const std::shared_ptr<Character>& character, std::unique_ptr<CharacterGraphicsItem> item)
{
    addItem(item.get());
    characters_.insert({ character, std::move(item) });
    characterMoved(character);
}

void GameScene::characterMoved(const std::shared_ptr<Character>& character)
{
    auto iter = characters_.find(character);
    if (iter != characters_.cend()) {
        auto pos = iter->first->moveData.location;
        iter->second->setPos(pos);
    }
}

void GameScene::cellChanged(size_t index)
{
    if (index < cellItems_.size()) {
        cellItems_[index]->update();
    }
}

} // namespace gui
} // namespace bm
