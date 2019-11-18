#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(LevelDeveloper);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
