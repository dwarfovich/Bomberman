#ifndef CLIENT_GAME_DIALOG_HPP
#define CLIENT_GAME_DIALOG_HPP

#include "game_creation_dialog.hpp"
#include "game_scene.hpp"
#include "game/game_status.hpp"

#include <QDir>

#include <QCoreApplication>

namespace Ui {
class ClientGameDialog;
}

namespace bm {
class Map;
class ClientGame;
class Client;

namespace gui {

// TODO: rename class, the name should be unified with other creation dialogs.
class ClientGameDialog : public GameCreationDialog
{
    Q_OBJECT

public:
    explicit ClientGameDialog(const std::shared_ptr<Player>& player, QWidget* parent = nullptr);
    ~ClientGameDialog();

    const GameInitializationData& initializationData() const override;

    Client* client() const;
    void    reset() override;

private slots:
    void onReady();
    void onLogMessageRequest(const QString& message);
    void connectToServer();
    void onConnectedToServer();
    void sendMessage();
    void changePlayerName();
    void onSelectMapRequest(QString mapFilename);
    void onGameStatusChanged(bm::GameStatus status);

private:
    ::Ui::ClientGameDialog*     ui_;
    std::shared_ptr<ClientGame> game_;
    Client*                     client_;
    QDir                        mapFolder_ = QDir::currentPath() + "/maps/";
    GameScene                   scene_;
    std::shared_ptr<Map>        selectedMap_;

    QTimer timer;

    // GameCreationDialog interface
public:
    const std::shared_ptr<Map>& map() const override;

    // QDialog interface
public slots:
    void accept() override;
};

} // namespace gui
} // namespace bm

#endif // CLIENT_GAME_DIALOG_HPP
