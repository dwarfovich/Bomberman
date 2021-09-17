#ifndef BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP
#define BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP

#include "game_scene.hpp"
#include "game_creation_dialog.hpp"
#include "game/game_initialization_data.hpp"
#include "game/network_game.hpp"

#include <QDir>
#include <QStandardItemModel>

namespace bm {
class Map;
class Server;

namespace gui {
namespace Ui {
class CreateNetworkGameDialog;
}

class CreateNetworkGameDialog : public GameCreationDialog
{
    Q_OBJECT

public:
    explicit CreateNetworkGameDialog(QWidget *parent = nullptr);
    ~CreateNetworkGameDialog();

    const GameInitializationData &initializationData() const override;

    Server *server() const;

public slots:
    void logMessage(const QString &message);
    void startServer();

private slots:
    void onServerPlayerNameChanged(const QString &newName);
    void onClientConnected(uint8_t clientId, const QString &name);
    void onClientNameChanged(uint8_t clientId, QString name);
    void onClientJoinedGame(uint8_t clientId);
    void onClientsWaitingForGameData();
    void onNewMapSelected(int index);
    void sendMessage();

private: // methods
    void addServerPlayerToModel();
    void prepareMapList();
    void addPlayerToModel(uint8_t clientId, const QString &name);

private: // data
    enum MapsComboBoxRoles
    {
        Filename = Qt::UserRole + 1
    };
    enum PlayersModelRoles
    {
        ClientId = Qt::UserRole + 1
    };

    Ui::CreateNetworkGameDialog *  ui_;
    const QDir                     mapFolder = QDir::currentPath() + "/maps/";
    QStandardItemModel             playersModel_;
    QStandardItemModel             mapsComboBoxModel_;
    Server *                       server_;
    std::shared_ptr<Map>           selectedMap_;
    GameScene                      scene_;
    std::shared_ptr<NetworkGame>   game_;
    mutable GameInitializationData initializationData_;
    QIcon                          playerConnectedIcon_ { ":/gui/player_connected.png" };
    QIcon                          playerReadyIcon_ { ":/gui/player_ready.png" };
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP
