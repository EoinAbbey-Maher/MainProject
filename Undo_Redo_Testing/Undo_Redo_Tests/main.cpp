
#include <QtWidgets>

#include "mainwindow.h"

//! [0]
int main(int argv, char *args[])
{
    Q_INIT_RESOURCE(Undo_Redo_Tests);

    QApplication app(argv, args);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
//! [0]
