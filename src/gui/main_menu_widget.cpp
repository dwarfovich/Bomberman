#include "main_menu_widget.hpp"
#include "ui_main_menu_widget.h"
#include "create_player_dialog.hpp"

#include <QDir>
#include <QDataStream>
#include <QMessageBox>

namespace bm {
namespace gui {

MainMenuWidget::MainMenuWidget(QWidget* parent) : QWidget(parent), ui_(new ::Ui::MainMenuWidget)
{
    ui_->setupUi(this);

    connect(ui_->playerNameComboBox,
            &QComboBox::currentIndexChanged,
            this,
            &MainMenuWidget::onPlayerNamesComboIndexChanged);
    connect(ui_->playerNameComboBox, &QComboBox::activated, this, &MainMenuWidget::onPlayerNamesComboIndexChanged);
    connect(ui_->startCampainButton, &QPushButton::clicked, this, &MainMenuWidget::newSinglePlayerGameRequest);
    connect(ui_->startSkirmishButton, &QPushButton::clicked, this, &MainMenuWidget::newNetworkGameRequest);
    connect(ui_->joinNetworkGameButton, &QPushButton::clicked, this, &MainMenuWidget::connectToServerRequest);
    connect(ui_->startFastGameButton, &QPushButton::clicked, this, &MainMenuWidget::newSinglePlayerGameRequest);

    loadPlayers();
    if (players_.empty()) {
        createNewPlayer();
    }
    updatePlayerNamesComboBox();
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui_;
}

void MainMenuWidget::onPlayerNamesComboIndexChanged(int index)
{
    if (index == players_.size()) {
        bool created = createNewPlayer();
        ui_->playerNameComboBox->blockSignals(true);
        if (created) {
            updatePlayerNamesComboBox();
            ui_->playerNameComboBox->setCurrentIndex(static_cast<int>(players_.size()) - 1);
        } else {
            ui_->playerNameComboBox->setCurrentIndex(currentPlayerIndex_ == -1 ? 0 : currentPlayerIndex_);
        }
        ui_->playerNameComboBox->blockSignals(false);
    } else {
        currentPlayerIndex_ = index;
    }
}

void MainMenuWidget::loadPlayers()
{
    QDir        playersDir  = QDir::currentPath() + "/players/";
    const auto& playerFiles = playersDir.entryList({ "*.sav" }, QDir::Files);
    for (const auto& playerFile : playerFiles) {
        QFile file { playersDir.filePath(playerFile) };
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream stream { &file };
            auto        player = std::make_shared<Player>(playerFile);
            stream >> *player;
            players_.push_back(std::move(player));
        }
    }
}

bool MainMenuWidget::createNewPlayer()
{
    CreatePlayerDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        const auto& name     = dialog.playerName();
        const auto& filename = generateFilenameForPlayer(name);
        if (filename.isEmpty()) {
            QMessageBox::critical(
                this, "Critical error", "Cann't create file for player, please choose another player's name");
        } else {
            auto player = std::make_shared<Player>(QDir::currentPath() + "/players/" + filename);
            player->setName(name);
            players_.push_back(std::move(player));
            return true;
        }
    }

    return false;
}

QString MainMenuWidget::generateFilenameForPlayer(const QString& name) const
{
    auto playersDir = QDir::currentPath() + "/players/";
    if (QFile::exists(playersDir + name + ".sav")) {
        for (int i = 1; i <= 100; ++i) {
            auto filename = name + QString::number(i) + ".sav";
            if (!QFile::exists(playersDir + filename)) {
                return filename;
            }
        }
    } else {
        return name + ".sav";
    }

    return {};
}

void MainMenuWidget::updatePlayerNamesComboBox()
{
    ui_->playerNameComboBox->blockSignals(true);
    ui_->playerNameComboBox->clear();
    for (const auto& player : players_) {
        ui_->playerNameComboBox->addItem(player->name());
    }
    ui_->playerNameComboBox->addItem("Create new player");
    ui_->playerNameComboBox->blockSignals(false);
}

} // namespace gui
} // namespace bm
