#include "create_network_game_dialog.hpp"
#include "ui_create_network_game_dialog.h"
#include "net/server.hpp"

namespace bm {
namespace gui {

CreateNetworkGameDialog::CreateNetworkGameDialog(QWidget *parent)
    : QDialog { parent }, ui_ { new Ui::CreateNetworkGameDialog }, server_ { new Server { this } }
{
    ui_->setupUi(this);

    playersModel_.setColumnCount(1);
    ui_->playersView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui_->playersView->setModel(&playersModel_);
    addServerPlayerToModel();

    connect(server_, &Server::logMessageRequest, this, &CreateNetworkGameDialog::logMessage);

    connect(
        ui_->serverPlayerNameEdit, &QLineEdit::textChanged, this, &CreateNetworkGameDialog::onServerPlayerNameChanged);
    connect(ui_->startGameButton, &QPushButton::clicked, this, &CreateNetworkGameDialog::accept);
    connect(ui_->cancelButton, &QPushButton::clicked, this, &CreateNetworkGameDialog::reject);

    startServer();
}

CreateNetworkGameDialog::~CreateNetworkGameDialog()
{
    delete ui_;
}

Server *CreateNetworkGameDialog::server() const
{
    return server_;
}

void CreateNetworkGameDialog::logMessage(const QString &message)
{
    ui_->logView->appendPlainText(message);
}

void CreateNetworkGameDialog::startServer()
{
    QHostAddress address;
    address.setAddress(ui_->serverAddressEdit->text());
    server_->startListen(address, ui_->serverPortSpinBox->value());
    //    ui->log->appendPlainText("Starting server: listen on " + address.toString() + ", port "
    //                             + QString::number(server->serverPort()));
}

void CreateNetworkGameDialog::onServerPlayerNameChanged(const QString &newName)
{
    auto item = playersModel_.item(0, 0);
    if (item) {
        item->setText(newName);
    }
}

void CreateNetworkGameDialog::addServerPlayerToModel()
{
    auto item = new QStandardItem { ui_->serverPlayerNameEdit->text() };
    playersModel_.appendRow(item);
}

} // namespace gui
} // namespace bm
