#include "create_network_game_dialog.hpp"
#include "ui_create_network_game_dialog.h"
#include "game/map_loader.hpp"
#include "net/server.hpp"
#include "net/text_message.hpp"
#include "net/select_map_request_message.hpp"

#include <QJsonDocument>
#include <QJsonObject>

namespace bm {
namespace gui {

CreateNetworkGameDialog::CreateNetworkGameDialog(QWidget *parent)
    : QDialog { parent }, ui_ { new Ui::CreateNetworkGameDialog }, server_ { new Server { this } }
{
    ui_->setupUi(this);

    ui_->mapPreview->setScene(&scene_);

    playersModel_.setColumnCount(1);
    ui_->playersView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui_->playersView->setModel(&playersModel_);
    addServerPlayerToModel();

    connect(server_, &Server::logMessageRequest, this, &CreateNetworkGameDialog::logMessage);
    connect(
        server_, &Server::allClientsWaitingForGameData, this, &CreateNetworkGameDialog::onClientsWaitingForGameData);
    connect(server_, &Server::clientConnected, this, &CreateNetworkGameDialog::onClientConnected);
    connect(server_, &Server::clientNameChanged, this, &CreateNetworkGameDialog::onClientNameChanged);

    connect(ui_->sendMessageButton, &QPushButton::clicked, this, &CreateNetworkGameDialog::sendMessage);
    connect(
        ui_->serverPlayerNameEdit, &QLineEdit::textChanged, this, &CreateNetworkGameDialog::onServerPlayerNameChanged);
    connect(ui_->startGameButton, &QPushButton::clicked, this, &CreateNetworkGameDialog::accept);
    connect(ui_->cancelButton, &QPushButton::clicked, this, &CreateNetworkGameDialog::reject);
    connect(ui_->mapComboBox, &QComboBox::currentIndexChanged, this, &CreateNetworkGameDialog::onNewMapSelected);

    ui_->startGameButton->setDisabled(true);

    prepareMapList();

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
}

void CreateNetworkGameDialog::onServerPlayerNameChanged(const QString &newName)
{
    auto item = playersModel_.item(0, 0);
    if (item) {
        item->setText(newName);
    }
}

void CreateNetworkGameDialog::onClientConnected(uint8_t clientId, QString name)
{
    auto *modelItem = new QStandardItem { name };
    modelItem->setData(clientId, PlayersModelRoles::ClientId);
    playersModel_.appendRow(modelItem);

    const auto &            selectedMapFileName = ui_->mapComboBox->currentData(MapsComboBoxRoles::Filename).toString();
    SelectMapRequestMessage message { selectedMapFileName };
    server_->broadcastMessage(message);
}

void CreateNetworkGameDialog::onClientNameChanged(uint8_t clientId, QString name)
{
    for (int i = 0; i < playersModel_.rowCount(); ++i) {
        auto *item = playersModel_.item(i);
        if (static_cast<uint8_t>(item->data(PlayersModelRoles::ClientId).toUInt()) == clientId) {
            item->setText(name);
            return;
        }
    }
}

void CreateNetworkGameDialog::onClientsWaitingForGameData()
{
    logMessage("Ready to start game");
    ui_->startGameButton->setEnabled(true);
}

void CreateNetworkGameDialog::onNewMapSelected(int index)
{
    const auto *const modelItem = mapsComboBoxModel_.item(index, 0);
    const auto &      fileName  = modelItem->data(MapsComboBoxRoles::Filename).toString();
    const auto &      filePath  = mapFolder.filePath(fileName);
    const auto &      mapData   = map_loader::loadFromFile(filePath);
    if (mapData.map) {
        selectedMap_ = mapData.map;
        scene_.setMap(selectedMap_);
        ui_->mapPreview->fitInView(ui_->mapPreview->rect(), Qt::KeepAspectRatio);
        SelectMapRequestMessage message { fileName };
        server_->broadcastMessage(message);
    } else {
        logMessage("Failed to load map from " + fileName);
    }
}

void CreateNetworkGameDialog::sendMessage()
{
    TextMessage message { ui_->serverPlayerNameEdit->text() + ": " + ui_->messageEdit->toPlainText() };
    server_->broadcastMessage(message);
    logMessage("You: " + ui_->messageEdit->toPlainText());
}

void CreateNetworkGameDialog::addServerPlayerToModel()
{
    auto item = new QStandardItem { ui_->serverPlayerNameEdit->text() };
    playersModel_.appendRow(item);
}

void CreateNetworkGameDialog::prepareMapList()
{
    const auto &fileNames = mapFolder.entryList(QStringList {} << "*.json", QDir::Files);
    for (const auto &fileName : fileNames) {
        const auto &filePath = mapFolder.filePath(fileName);
        QFile       file { filePath };
        if (!file.open(QIODevice::ReadOnly)) {
            logMessage("Cann't open map for file " + fileName);
            continue;
        }

        auto            jsonData = file.readAll();
        QJsonParseError error;
        auto            document = QJsonDocument::fromJson(jsonData, &error);
        if (error.error != QJsonParseError::NoError) {
            logMessage("Cann't parse map from " + fileName);
            continue;
        }

        const auto &jsonObject = document.object();
        const auto &mapName    = jsonObject["name"].toString();
        auto        modelItem  = new QStandardItem { mapName };
        modelItem->setData(fileName, MapsComboBoxRoles::Filename);
        mapsComboBoxModel_.appendRow(modelItem);
    }
    ui_->mapComboBox->setModel(&mapsComboBoxModel_);
}

} // namespace gui
} // namespace bm
