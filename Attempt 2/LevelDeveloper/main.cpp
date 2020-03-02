#include "mainwindow.h"
#include "startupscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(LevelDeveloper);

    QApplication a(argc, argv);
    StartupScreen w;
    w.show();
    return a.exec();
}
