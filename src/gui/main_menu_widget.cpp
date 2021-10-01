#include "main_menu_widget.hpp"
#include "ui_main_menu_widget.h"
#include "create_player_dialog.hpp"
#include "game/game_utils.hpp"

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
    connect(ui_->startCampainButton, &QPushButton::clicked, this, &MainMenuWidget::campaignGameRequest);
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

const std::shared_ptr<Player> MainMenuWidget::selectedPlayer() const
{
    auto playerIndex = ui_->playerNameComboBox->currentIndex();
    if (playerIndex < players_.size()) {
        return players_[playerIndex];
    } else {
        static const std::shared_ptr<Player> empty;
        return empty;
    }
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
    auto playersFolder = QDir::currentPath() + "/players/";
    players_           = game_utils::loadPlayers(playersFolder);
}

bool MainMenuWidget::createNewPlayer()
{
    CreatePlayerDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        const auto& name     = dialog.playerName();
        const auto& filename = game_utils::generateFilenameForPlayer(name, QDir::currentPath() + "/players/");
        if (filename.isEmpty()) {
            QMessageBox::critical(
                this, "Critical error", "Cann't create file for player, please choose another player's name");
        } else {
            auto player = std::make_shared<Player>(QDir::currentPath() + "/players/" + filename);
            player->setName(name);
            auto result = game_utils::savePlayer(*player, QDir::currentPath() + "/players/");
            if (result) {
                players_.push_back(std::move(player));
                return true;
            } else {
                QMessageBox::critical(this, "Critical error", "Cann't save player.");
            }
        }
    }

    return false;
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
