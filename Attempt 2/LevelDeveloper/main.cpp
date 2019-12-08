#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(LevelDeveloper);

    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    MainWindow w;
    w.show();

    return a.exec();
}
