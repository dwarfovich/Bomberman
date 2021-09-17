#include "main_menu_widget.hpp"
#include "ui_main_menu_widget.h"

namespace bm {
namespace gui {

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent), ui_(new Ui::MainMenuWidget)
{
    ui_->setupUi(this);

    connect(ui_->startCampainButton, &QPushButton::clicked, this, &MainMenuWidget::newSinglePlayerGameRequest);
    connect(ui_->startSkirmishButton, &QPushButton::clicked, this, &MainMenuWidget::newNetworkGameRequest);
    connect(ui_->joinNetworkGameButton, &QPushButton::clicked, this, &MainMenuWidget::connectToServerRequest);
    connect(ui_->startFastGameButton, &QPushButton::clicked, this, &MainMenuWidget::newSinglePlayerGameRequest);
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui_;
}

} // namespace gui
} // namespace bm
