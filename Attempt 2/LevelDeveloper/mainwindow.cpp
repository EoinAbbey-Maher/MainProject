#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    initScene();

    View *view =  new View("MainView");
    view->m_view()->setScene(m_scene);

    setWindowTitle(tr("2D Level Editor"));
}

void MainWindow::initScene()
{
    m_scene = new QGraphicsScene(this);

    QImage *image = new QImage();
    bool loaded = image->load(":/floor.png");

    //Initialise Scene
    int row = 0;
    int noOfItems = 0;

    for (int i= -11000; i < 11000; i+= 110)
    {
        ++row;
        int col = 0;
        for (int j = -7000; j < 7000; j+= 70)
        {
            ++row;
            qreal x = (i + 11000) / 22000;
            qreal y = (j + 7000) / 14000;

            QColor color(image->pixel(int(image->width() * x), int( image->height() * y)));
            QGraphicsItem *item = new Tile(color, row, col);
            item->setPos(QPointF(i,j));
            m_scene->addItem(item);

            ++noOfItems;
        }

    }

}


void MainWindow::setupMatrix()
{

}



//MainWindow::MainWindow(QWidget *parent)
//    : QMainWindow(parent)
//    , ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//    setupIcons();
//    setupGameGrid();

//    connect(ui->m_applyButton, SIGNAL(released()), this,SLOT(handleApplyButton()));

//}

//MainWindow::~MainWindow()
//{
//    delete ui;
//}

//void MainWindow::handleApplyButton()
//{
//    ui->m_applyButton->setText("Pressed");
//    setTextures();
//}

//// ------------------------------------------------------------------------------------
////            Assign Textures From Button Press
//// ------------------------------------------------------------------------------------
//void MainWindow::setTextures()
//{
//    for (int i = 0; i < ui->Game_Table->selectedItems().count(); i++)
//    {
//        ui->Game_Table->selectedItems().at(i)->setData(Qt::DecorationRole, ui->Icon_Table->selectedItems().at(0)->data(Qt::DecorationRole).value<QPixmap>());
//    }

//    qDebug() << "setup Textures";
//}

//// ------------------------------------------------------------------------------------
////            Assign Textures From Button Press
//// ------------------------------------------------------------------------------------
//void MainWindow::setupIcons()
//{

//    QString imgString = ":/floor.jpg";
//    QImage *img = new QImage();
//    bool loaded = img->load(imgString);

//    if(loaded)
//    {

//        for (int r = 0; r < ui->Icon_Table ->rowCount(); r++)
//           {
//               for (int c = 0; c < ui->Icon_Table ->columnCount(); c++)
//                {
//                    QTableWidgetItem * item = new QTableWidgetItem;
//                    item->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
//                    ui->Icon_Table ->setItem(r,c,item);
//                }
//          }
//    }
//    else
//    {
//        qDebug() << "image not loaded";

//    }

//        ui->Icon_Table->setSelectionMode(QAbstractItemView::SingleSelection);
//        ui->Icon_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);


//}

//// ------------------------------------------------------------------------------------
////            Assign Textures From Button Press
//// ------------------------------------------------------------------------------------
//void MainWindow::setupGameGrid()
//{



//        for (int r = 0; r < ui->Game_Table ->rowCount(); r++)
//           {
//               for (int c = 0; c < ui->Game_Table->columnCount(); c++)
//                {
//                    QTableWidgetItem * item = new QTableWidgetItem;
//                    ui->Game_Table->setItem(r,c,item);
//                }
//          }

//        ui->Game_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    QGraphicsProxyWidget *pr = scene->addWidget(ui->Game_Table);

//    ui->m_graphicsView->setScene(scene);

//    pr->moveBy(10,10);

//}


