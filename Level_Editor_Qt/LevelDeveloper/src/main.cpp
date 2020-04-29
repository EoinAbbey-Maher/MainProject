/**
*    main.cpp
*    @author Eoin Abbey-Maher
*    @brief Entry Point for Application
*/

#include "include/mainwindow.h"
#include "include/startingscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(LevelDeveloper);

    QApplication a(argc, argv);
    StartingScreen w;
    w.show();
    return a.exec();
}
