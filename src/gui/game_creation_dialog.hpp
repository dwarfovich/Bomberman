#ifndef BM_GUI_GAMECREATIONDIALOG_HPP
#define BM_GUI_GAMECREATIONDIALOG_HPP

#include <QDialog>

#include <memory>

namespace bm {
class Map;
class GameInitializationData;

namespace gui {

class GameCreationDialog : public QDialog
{
public:
    explicit GameCreationDialog(QWidget* parent = nullptr);

    // TODO: may be just return GameInitializationData by value?
    virtual const GameInitializationData& initializationData() const = 0;
    // TODO: remove.
    virtual const std::shared_ptr<Map>& map() const;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_GAMECREATIONDIALOG_HPP
