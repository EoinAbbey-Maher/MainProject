
#include <QApplication>
#include <QHBoxLayout>
#include <QTableWidget>

#include "DragWidget.h"
#include "selectablegrid.h"
#include "gamegrid.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Linux);

    QApplication a(argc, argv);

    QWidget *mainWidget = new QWidget;

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(new GameGrid);
   // layout->addWidget(new QTableWidget(20,20));
    layout->addWidget(new SelectableGrid);
    layout->addWidget(new DragWidget);


    mainWidget->setWindowTitle(QObject::tr("Starter Testing"));
    mainWidget->setLayout(layout);
    mainWidget->show();

    return a.exec();
}
