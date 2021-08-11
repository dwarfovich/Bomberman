#include "client_game_dialog.hpp"
#include "ui_client_game_dialog.h"
#include "net/client.hpp"
#include "net/text_message.hpp"

#include <QHostAddress>

namespace bm {

ClientGameDialog::ClientGameDialog(QWidget *parent)
    : QDialog(parent), ui_(new Ui::ClientGameDialog), client_ { new Client { this } }
{
    ui_->setupUi(this);

    connect(client_, &Client::logMessage, this, &ClientGameDialog::onLogMessageRequest);

    connect(ui_->connectButton, &QPushButton::clicked, this, &ClientGameDialog::connectToServer);
    connect(ui_->sendMessageButton, &QPushButton::clicked, this, &ClientGameDialog::sendMessage);
}

ClientGameDialog::~ClientGameDialog()
{
    delete ui_;
}

void ClientGameDialog::onLogMessageRequest(const QString &message)
{
    ui_->logView->append(message);
}

void ClientGameDialog::connectToServer()
{
    QHostAddress address { ui_->serverAddressEdit->text() };
    client_->connectToServer(address, ui_->portSpinBox->value());
}

void ClientGameDialog::sendMessage()
{
    const auto &text = ui_->messageEdit->toPlainText();
    if (!text.isEmpty()) {
        TextMessage message { text };
        client_->sendMessage(message);
        onLogMessageRequest("Sending message: " + text);
    }
}

} // namespace bm
