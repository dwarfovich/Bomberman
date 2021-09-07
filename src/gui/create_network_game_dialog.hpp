#ifndef BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP
#define BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP

#include "game_scene.hpp"

#include <QDialog>
#include <QDir>
#include <QStandardItemModel>

namespace bm {
class Map;
class Server;

namespace gui {
namespace Ui {
class CreateNetworkGameDialog;
}

class CreateNetworkGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateNetworkGameDialog(QWidget *parent = nullptr);
    ~CreateNetworkGameDialog();

    Server *server() const;

public slots:
    void logMessage(const QString &message);
    void startServer();

private slots:
    void onServerPlayerNameChanged(const QString &newName);
    void onClientConnected(uint8_t clientId, QString name);
    void onClientNameChanged(uint8_t clientId, QString name);
    void onClientsWaitingForGameData();
    void onNewMapSelected(int index);
    void sendMessage();

private: // methods
    void addServerPlayerToModel();
    void prepareMapList();

private: // data
    enum MapsComboBoxRoles
    {
        Filename = Qt::UserRole + 1
    };
    enum PlayersModelRoles
    {
        ClientId = Qt::UserRole + 1
    };

    Ui::CreateNetworkGameDialog *ui_;
    const QDir                   mapFolder = QDir::currentPath() + "/maps/";
    QStandardItemModel           playersModel_;
    QStandardItemModel           mapsComboBoxModel_;
    Server *                     server_;
    std::shared_ptr<Map>         selectedMap_;
    GameScene                    scene_;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP
