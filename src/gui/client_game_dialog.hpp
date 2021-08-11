#ifndef CLIENT_GAME_DIALOG_HPP
#define CLIENT_GAME_DIALOG_HPP

#include <QDialog>

namespace Ui {
class ClientGameDialog;
}

namespace bm {
class Client;

class ClientGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientGameDialog(QWidget* parent = nullptr);
    ~ClientGameDialog();

private slots:
    void onLogMessageRequest(const QString& message);
    void connectToServer();
    void sendMessage();

private:
    Ui::ClientGameDialog* ui_;
    Client*               client_;
};

} // namespace bm
#endif // CLIENT_GAME_DIALOG_HPP
