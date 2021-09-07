#ifndef CLIENT_GAME_DIALOG_HPP
#define CLIENT_GAME_DIALOG_HPP

#include "game_scene.hpp"

#include <QDialog>
#include <QDir>

namespace Ui {
class ClientGameDialog;
}

namespace bm {
class Map;
class Client;

namespace gui {

class ClientGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientGameDialog(QWidget* parent = nullptr);
    ~ClientGameDialog();

    Client* client() const;

private slots:
    void onReady();
    void onLogMessageRequest(const QString& message);
    void connectToServer();
    void sendMessage();
    void changePlayerName();
    void onSelectMapRequest(QString mapFilename);
    void onReadyForPreparingToStartGame();

private:
    ::Ui::ClientGameDialog* ui_;
    Client*                 client_;
    QDir                    mapFolder_ = QDir::currentPath() + "/maps/";
    GameScene               scene_;
    std::shared_ptr<Map>    selectedMap_;
};

} // namespace gui
} // namespace bm

#endif // CLIENT_GAME_DIALOG_HPP
