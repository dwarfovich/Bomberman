#ifndef BM_GUI_GAMECREATIONDIALOG_HPP
#define BM_GUI_GAMECREATIONDIALOG_HPP

#include <QDialog>

#include <memory>

namespace bm {
class Map;
class GameInitializationData;
class Player;

namespace gui {

class GameCreationDialog : public QDialog
{
public:
    explicit GameCreationDialog(QWidget* parent = nullptr, const std::shared_ptr<Player>& player = nullptr);

    virtual void reset();

    // TODO: may be just return GameInitializationData by value?
    virtual const GameInitializationData& initializationData() const = 0;
    // TODO: remove.
    virtual const std::shared_ptr<Map>& map() const;

    const std::shared_ptr<Player>& player() const;
    void                           setPlayer(const std::shared_ptr<Player>& newPlayer);

protected:
    std::shared_ptr<Player> player_;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_GAMECREATIONDIALOG_HPP
