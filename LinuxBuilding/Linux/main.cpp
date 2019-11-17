
#include <QApplication>
#include <QHBoxLayout>
#include <QTableWidget>

#include "DragWidget.h"
#include "selectablegrid.h"


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(Linux);

    QApplication a(argc, argv);

    QWidget *mainWidget = new QWidget;

    SelectableGrid * selectablegrid = new SelectableGrid();
    QHBoxLayout *layout = new QHBoxLayout;
    //layout->addWidget(new GameGrid);
    layout->addLayout(selectablegrid->layout);
    //layout->addWidget(new DragWidget);

    mainWidget->setWindowTitle(QObject::tr("Starter Testing"));
    mainWidget->setLayout(layout);
    mainWidget->show();



    return a.exec();
}
