#include "client_game_dialog.hpp"
#include "ui_client_game_dialog.h"
#include "game/map_loader.hpp"
#include "net/client.hpp"
#include "net/messages/text_message.hpp"
#include "net/messages/player_ready_message.hpp"
#include "net/messages/client_joining_game_message.hpp"

#include <QHostAddress>

namespace bm {
namespace gui {

ClientGameDialog::ClientGameDialog(QWidget *parent)
    : QDialog(parent), ui_(new ::Ui::ClientGameDialog), client_ { new Client { this } }
{
    ui_->setupUi(this);

    ui_->mapPreview->setScene(&scene_);

    connect(client_, &Client::logMessage, this, &ClientGameDialog::onLogMessageRequest);
    connect(client_, &Client::readyToStartGame, this, &ClientGameDialog::accept);
    connect(client_, &Client::selectMapRequest, this, &ClientGameDialog::onSelectMapRequest);

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
    ClientJoiningGameMessage message;
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

void ClientGameDialog::onSelectMapRequest(QString mapFilename)
{
    const auto &mapFilePath = mapFolder_.filePath(mapFilename);
    auto        mapData     = map_loader::loadFromFile(mapFilePath);
    if (mapData.map) {
        selectedMap_ = mapData.map;
        scene_.setMap(selectedMap_);
        ui_->mapPreview->fitInView(scene_.sceneRect(), Qt::KeepAspectRatio);
        ui_->mapNameEdit->setText(selectedMap_->name());
    } else {
        onLogMessageRequest("Cann't load map preview for file " + mapFilePath);
    }
}

void ClientGameDialog::onReadyForPreparingToStartGame()
{}

} // namespace gui
} // namespace bm
