#include "gui/main_window.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication        a { argc, argv };
    bm::gui::MainWindow w;

    w.show();
    return a.exec();
}
