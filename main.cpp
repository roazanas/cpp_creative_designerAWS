#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
