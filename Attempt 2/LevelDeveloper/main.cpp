#include "mainwindow.h"
#include "startingscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(LevelDeveloper);

    QApplication a(argc, argv);
    StartingScreen w;
    w.show();
    return a.exec();
}
