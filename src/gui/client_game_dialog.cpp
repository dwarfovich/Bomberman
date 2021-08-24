#include "client_game_dialog.hpp"
#include "ui_client_game_dialog.h"
#include "net/client.hpp"
#include "net/text_message.hpp"
#include "net/client_ready_message.hpp"

#include <QHostAddress>

namespace bm {
namespace gui {

ClientGameDialog::ClientGameDialog(QWidget *parent)
    : QDialog(parent), ui_(new ::Ui::ClientGameDialog), client_ { new Client { this } }
{
    ui_->setupUi(this);

    connect(client_, &Client::logMessage, this, &ClientGameDialog::onLogMessageRequest);
    // connect(client_, &Client::readyForPreparingToGameStart, this, &ClientGameDialog::onReadyForPreparingToStartGame);
    // connect(client_, &Client::readyForPreparingToGameStart, this, &ClientGameDialog::accepted);
    connect(client_, &Client::readyToStartGame, this, &ClientGameDialog::accept);
    // connect(client_, &Client::readyToStartGame, this, &ClientGameDialog::onReadyToStartGame);

    connect(ui_->connectButton, &QPushButton::clicked, this, &ClientGameDialog::connectToServer);
    connect(ui_->sendMessageButton, &QPushButton::clicked, this, &ClientGameDialog::sendMessage);
    connect(ui_->readyButton, &QPushButton::clicked, this, &ClientGameDialog::onReady);
    connect(ui_->playerNameEdit, &QLineEdit::editingFinished, this, &ClientGameDialog::changePlayerName);

    changePlayerName();
}

ClientGameDialog::~ClientGameDialog()
{
    delete ui_;
}

Client *ClientGameDialog::client() const
{
    return client_;
}

void ClientGameDialog::onReady()
{
    ClientReadyMessage message(client_->id());
    client_->sendMessage(message);
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
        onLogMessageRequest("You: " + text);
    }
}

void ClientGameDialog::changePlayerName()
{
    client_->setName(ui_->playerNameEdit->text());
}

void ClientGameDialog::onReadyForPreparingToStartGame()
{}

} // namespace gui
} // namespace bm
