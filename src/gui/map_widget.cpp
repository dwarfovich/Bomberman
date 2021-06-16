#include "map_widget.hpp"
#include "ui_map_widget.h"

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapWidget)
{
    ui->setupUi(this);
}

MapWidget::~MapWidget()
{
    delete ui;
}
