#include "client_game_dialog.hpp"
#include "ui_client_game_dialog.h"
#include "game/map_loader.hpp"
#include "game/client_game.hpp"
#include "game/game_initialization_data.hpp"
#include "net/client.hpp"
#include "net/messages/text_message.hpp"
#include "net/messages/client_name_message.hpp"
#include "net/messages/player_ready_message.hpp"
#include "net/messages/client_joining_game_message.hpp"

#include <QHostAddress>

namespace bm {
namespace gui {

ClientGameDialog::ClientGameDialog(const std::shared_ptr<Player> &player, QWidget *parent)
    : GameCreationDialog { parent, player }, ui_(new ::Ui::ClientGameDialog), client_ { new Client { this } }
{
    ui_->setupUi(this);

    game_ = std::make_shared<ClientGame>(client_);
    game_->addPlayer(player_);

    ui_->mapPreview->setScene(&scene_);

    ui_->playerNameEdit->setText(player->name());
    qDebug() << "player:" << player->name();

    connect(game_.get(), &Game::gameStatusChanged, this, &ClientGameDialog::onGameStatusChanged);

    connect(client_, &Client::logMessage, this, &ClientGameDialog::onLogMessageRequest);
    connect(client_, &Client::connectedToServer, this, &ClientGameDialog::onConnectedToServer);
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

void ClientGameDialog::reset()
{
    game_->reset();
}

void ClientGameDialog::onReady()
{
    ClientJoiningGameMessage message { *player_ };
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

void ClientGameDialog::onConnectedToServer()
{
    ClientNameMessage message { ui_->playerNameEdit->text() };
    client_->sendMessage(message);
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

void ClientGameDialog::onGameStatusChanged(GameStatus status)
{
    if (status == GameStatus::PreparingFinished) {
        accept();
    }
}

const GameInitializationData &ClientGameDialog::initializationData() const
{
    static GameInitializationData data;
    data.game            = game_;
    data.map             = game_->map();
    data.playerBomberman = game_->playerId();

    return data;
}

} // namespace gui
} // namespace bm

const std::shared_ptr<bm::Map> &bm::gui::ClientGameDialog::map() const
{
    if (game_) {
        return game_->map();

    } else {
        static const std::shared_ptr<Map> empty { nullptr };
        return empty;
    }
}

void bm::gui::ClientGameDialog::accept()
{
    qDebug() << "ClientGameDialog::accept()";
    QDialog::accept();
}
