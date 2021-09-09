#ifndef CLIENT_GAME_DIALOG_HPP
#define CLIENT_GAME_DIALOG_HPP

#include "game_creation_dialog.hpp"
#include "game_scene.hpp"
#include "game/game_status.hpp"

#include <QDir>

namespace Ui {
class ClientGameDialog;
}

namespace bm {
class Map;
class ClientGame;
class Client;

namespace gui {

class ClientGameDialog : public GameCreationDialog
{
    Q_OBJECT

public:
    explicit ClientGameDialog(QWidget* parent = nullptr);
    ~ClientGameDialog();

    const GameInitializationData& initializationData() const override;

    Client* client() const;

private slots:
    void onReady();
    void onLogMessageRequest(const QString& message);
    void connectToServer();
    void sendMessage();
    void changePlayerName();
    void onSelectMapRequest(QString mapFilename);
    void onReadyForPreparingToStartGame();
    void onGameStatusChanged(GameStatus status);

private:
    ::Ui::ClientGameDialog*     ui_;
    std::shared_ptr<ClientGame> game_;
    Client*                     client_;
    QDir                        mapFolder_ = QDir::currentPath() + "/maps/";
    GameScene                   scene_;
    std::shared_ptr<Map>        selectedMap_;
};

} // namespace gui
} // namespace bm

#endif // CLIENT_GAME_DIALOG_HPP
