#include "main_menu_widget.hpp"
#include "ui_main_menu_widget.h"

namespace bm {
namespace gui {

MainMenuWidget::MainMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenuWidget)
{
    ui->setupUi(this);

    connect(ui->newSinglePlayerGameButton, &QPushButton::clicked, this, &MainMenuWidget::newSinglePlayerGameRequest);
    connect(ui->newNetworkGameButton, &QPushButton::clicked, this, &MainMenuWidget::newNetworkGameRequest);
    connect(ui->connectToServerButton, &QPushButton::clicked, this, &MainMenuWidget::connectToServerRequest);
}

MainMenuWidget::~MainMenuWidget()
{
    delete ui;
}

} // namespace gui
} // namespace bm
