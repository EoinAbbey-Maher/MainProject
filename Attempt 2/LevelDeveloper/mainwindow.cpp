#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupIcons();
    setupGameGrid();

    connect(ui->m_applyButton, SIGNAL(released()), this,SLOT(handleApplyButton()));
    connect(ui->m_clearCellButton, SIGNAL(released()),this,SLOT(handleClearButton()));
    connect(ui->Icon_Table, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));
    connect(ui->Game_Table, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::handleApplyButton()
{
    //ui->m_applyButton->setText("Pressed");
if(ui->Game_Table->selectedItems().size() != 0 && ui->Icon_Table->selectedItems().size() != 0)
{
    setTextures();
}

}

void MainWindow::handleClearButton()
{
    if(ui->Game_Table->selectedItems().size() != 0)
    {
        removeTextures();
    }
}

// ------------------------------------------------------------------------------------
//            Assign Textures From Button Press
// ------------------------------------------------------------------------------------
void MainWindow::setTextures()
{
    for (int i = 0; i < ui->Game_Table->selectedItems().count(); i++)
    {
        ui->Game_Table->selectedItems().at(i)->setData(Qt::DecorationRole, ui->Icon_Table->selectedItems().at(0)->data(Qt::DecorationRole).value<QPixmap>());
    }

    qDebug() << "setup Textures";
}

// ------------------------------------------------------------------------------------
//            Remove Texture From Cell
// ------------------------------------------------------------------------------------
void MainWindow::removeTextures()
{
    QString imgString = ":/empty.png";
    QImage *emptyImg = new QImage();

    for (int i = 0; i < ui->Game_Table->selectedItems().count(); i++)
    {
        ui->Game_Table->selectedItems().at(i)->setData(Qt::DecorationRole, QPixmap::fromImage(*emptyImg));
    }
}

// ------------------------------------------------------------------------------------
//            Assign Textures From Button Press
// ------------------------------------------------------------------------------------
void MainWindow::setupIcons()
{

    QString imgString = ":/floor.png";
    QImage *img = new QImage();
    bool loaded = img->load(imgString);

    if(loaded)
    {

        for (int r = 0; r < ui->Icon_Table ->rowCount(); r++)
           {
               for (int c = 0; c < ui->Icon_Table ->columnCount(); c++)
                {
                    QTableWidgetItem * item = new QTableWidgetItem;
                    item->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
                    ui->Icon_Table ->setItem(r,c,item);
                }
          }
    }
    else
    {
        qDebug() << "image not loaded";

    }

        ui->Icon_Table->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->Icon_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);


}

// ------------------------------------------------------------------------------------
//            Assign Textures From Button Press
// ------------------------------------------------------------------------------------
void MainWindow::setupGameGrid()
{
        for (int r = 0; r < ui->Game_Table ->rowCount(); r++)
           {
               for (int c = 0; c < ui->Game_Table->columnCount(); c++)
                {
                    QTableWidgetItem * item = new QTableWidgetItem;
                    ui->Game_Table->setItem(r,c,item);
                }
          }

        ui->Game_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QGraphicsProxyWidget *pr = scene->addWidget(ui->Game_Table);


    pr->moveBy(10,10);
}


