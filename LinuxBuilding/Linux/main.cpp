#include "mainwindow.h"

#include <QApplication>
#include <QHBoxLayout>

#include "DragWidget.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Linux);

    QApplication a(argc, argv);

    QWidget mainWidget;
    QHBoxLayout * horizontalLayout = new QHBoxLayout(&mainWidget);
    horizontalLayout->addWidget(new DragWidget);
   horizontalLayout->addWidget(new DragWidget);

    mainWidget.setWindowTitle(QObject::tr("Starter Testing"));
    mainWidget.show();

    return a.exec();
}
