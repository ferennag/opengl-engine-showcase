#include <QApplication>
#include "ui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.resize(1920, 1080);
    mainWindow.show();
    return QApplication::exec();
}
