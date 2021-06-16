#include "gui/main_window.hpp"

#include <QApplication>

struct A {
    int aval;
};

struct B : public A {
    int bval;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bm::gui::MainWindow w;

    w.show();
    return (a.exec());
}
