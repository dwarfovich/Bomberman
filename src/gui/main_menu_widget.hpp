#ifndef MAIN_MENU_WIDGET_HPP
#define MAIN_MENU_WIDGET_HPP

#include <QWidget>

namespace Ui {
class MainMenuWidget;
}

namespace bm {
namespace gui {

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget *parent = nullptr);
    ~MainMenuWidget();

signals:
    void newSinglePlayerGameRequest();
    void newNetworkGameRequest();

private:
    Ui::MainMenuWidget *ui;
};

} // namespace gui
} // namespace bm

#endif // MAIN_MENU_WIDGET_HPP
