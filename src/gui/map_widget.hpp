#ifndef MAP_WIDGET_H
#define MAP_WIDGET_H

#include <QWidget>

// TODO: Delete MapWidget if it's unused.
namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = nullptr);
    ~MapWidget();

private:
    Ui::MapWidget *ui;
};

#endif // MAP_WIDGET_H
