#ifndef BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP
#define BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP

#include <QDialog>
#include <QStandardItemModel>

namespace bm {
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

public slots:
    void logMessage(const QString &message);
    void startServer();

private slots:
    void onServerPlayerNameChanged(const QString &newName);

private: // methods
    void addServerPlayerToModel();

private: // data
    Ui::CreateNetworkGameDialog *ui_;
    QStandardItemModel           playersModel_;
    Server *                     server_;
};

} // namespace gui
} // namespace bm

#endif // BM_GUI_CREATE_NETWORK_GAME_DIALOG_HPP
