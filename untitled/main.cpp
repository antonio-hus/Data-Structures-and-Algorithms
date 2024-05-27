#include <QApplication>
#include <QPushButton>
#include "GUI/gui.h"
#include "Controller/Controller.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Controller controller;
    GUI display(controller);
    display.show();
    return QApplication::exec();
}
