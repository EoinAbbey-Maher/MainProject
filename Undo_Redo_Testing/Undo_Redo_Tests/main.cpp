#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Undo_Redo_Tests);

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
