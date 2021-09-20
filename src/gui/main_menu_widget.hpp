#ifndef MAIN_MENU_WIDGET_HPP
#define MAIN_MENU_WIDGET_HPP

#include "game/player.hpp"

#include <QWidget>

#include <memory>
#include <vector>

namespace Ui {
class MainMenuWidget;
}

namespace bm {
namespace gui {

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget *parent = nullptr);
    ~MainMenuWidget();

signals:
    void newSinglePlayerGameRequest();
    void newNetworkGameRequest();
    void connectToServerRequest();

private slots:
    void onPlayerNamesComboIndexChanged(int index);

private:
    void    loadPlayers();
    bool    createNewPlayer();
    QString generateFilenameForPlayer(const QString &name) const;
    void    updatePlayerNamesComboBox();

private:
    Ui::MainMenuWidget *                 ui_;
    std::vector<std::shared_ptr<Player>> players_;
    int                                  currentPlayerIndex_ = -1;
};

} // namespace gui
} // namespace bm

#endif // MAIN_MENU_WIDGET_HPP
