#ifndef CLIENT_GAME_DIALOG_HPP
#define CLIENT_GAME_DIALOG_HPP

#include <QDialog>

namespace Ui {
class ClientGameDialog;
}

namespace bm {
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
    void onReadyForPreparingToStartGame();

private:
    ::Ui::ClientGameDialog* ui_;
    Client*                 client_;
};

} // namespace gui
} // namespace bm

#endif // CLIENT_GAME_DIALOG_HPP
