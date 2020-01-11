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
    connect(ui->m_exportButton, SIGNAL(released()), this, SLOT(handleExportButton()));

    connect(ui->Icon_Table, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));
    connect(m_mapTable, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleApplyButton()
{
    //ui->m_applyButton->setText("Pressed");
if( m_mapTable->selectedItems().size() != 0 && ui->Icon_Table->selectedItems().size() != 0)
{
    setTextures();
}

}

void MainWindow::handleClearButton()
{
    if(m_mapTable->selectedItems().size() != 0)
    {
        removeTextures();
    }
}

void MainWindow::handleExportButton()
{
    m_xmlWriter.WriteTilesToFile(ui->Icon_Table);
}

void MainWindow::createActions()
{
    setTextureAction = new QAction(tr("&Set Texture"), this);
    connect(ui->Icon_Table, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));
    connect( m_mapTable, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));
    connect(ui->m_applyButton, SIGNAL(released()), this,SLOT(handleApplyButton()));

    removeTextureAction = new QAction(tr("&Remove Textures"), this);
    connect(ui->m_clearCellButton, SIGNAL(released()),this,SLOT(handleClearButton()));

    undoAction = undoStack->createUndoAction(this, tr("&Undo"));
    undoAction->setShortcut(QKeySequence::Undo);

    redoAction = undoStack->createRedoAction(this,tr("&Redo"));
    undoAction->setShortcut(QKeySequence::Redo);
}

// ------------------------------------------------------------------------------------
//            Assign Textures From Button Press
// ------------------------------------------------------------------------------------
void MainWindow::setTextures()
{
    for (int i = 0; i <  m_mapTable->selectedItems().count(); i++)
    {
         m_mapTable->selectedItems().at(i)->setData(Qt::DecorationRole, ui->Icon_Table->selectedItems().at(0)->data(Qt::DecorationRole).value<QPixmap>());
         m_mapTable->selectedItems().at(i)->setData(Qt::UserRole, ui->Icon_Table->selectedItems().at(0)->data(Qt::UserRole));
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

    for (int i = 0; i <  m_mapTable->selectedItems().count(); i++)
    {
        m_mapTable->selectedItems().at(i)->setData(Qt::DecorationRole, QPixmap::fromImage(*emptyImg));
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
    img->scaled(50,50, Qt::KeepAspectRatio);

    QImage *img1= new QImage();
    QString img1String = ":/floor1.png";
    img1->load(":/floor1.png");
    img1->scaled(50,50, Qt::KeepAspectRatio);

    QImage *img2= new QImage();
    QString img2String = ":/floor2.png";
    img2->load(":/floor2.png");

    img2->scaled(50,50, Qt::KeepAspectRatio);

    QImage *img3= new QImage();
    QString img3String = ":/floor3.png";
    img3->load(":/floor3.png");
    img3->scaled(50,50, Qt::KeepAspectRatio);

    QImage *img4= new QImage();
    QString img4String = ":/empty.png";
    img4->load(":/empty.png");
    img4->scaled(50,50, Qt::KeepAspectRatio);

    if(loaded)
    {

        for (int r = 0; r < ui->Icon_Table ->rowCount(); r++)
           {
               for (int c = 0; c < ui->Icon_Table ->columnCount(); c++)
                {
                    TileItem * item = new TileItem;
                    switch(r){
                    case 0:
                        switch(c){
                        case 0:
                                item->setTexture(img);
                                item->setData(Qt::UserRole, imgString);
                                item->setIndexVal(QVector2D(r,c));
                                ui->Icon_Table->setItem(r,c,item);
                                    break;
                        case 1:
                                item->setTexture(img1);
                                item->setData(Qt::UserRole, img1String);
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img1));
                                item->setIndexVal(QVector2D(r,c));
                                ui->Icon_Table ->setItem(r,c,item);
                                    break;
                        case 2:
                                item->setTexture(img2);
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img2));
                                item->setData(Qt::UserRole, img2String);
                                item->setIndexVal(QVector2D(r,c));
                                ui->Icon_Table ->setItem(r,c,item);
                                    break;
                        case 3:
                                item->setTexture(img3);
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img3));
                                item->setData(Qt::UserRole, img3String);
                                item->setIndexVal(QVector2D(r,c));
                                ui->Icon_Table ->setItem(r,c,item);
                                    break;

                        default: break;
                        }
                        break;

                    default:
                        item->setTexture(img);
                        item->setData(Qt::UserRole, img4String);
                        item->setData(Qt::DecorationRole, QPixmap::fromImage(*img4));
                        item->setIndexVal(QVector2D(r,c));
                        ui->Icon_Table ->setItem(r,c,item);
                        break;
                    }
                }
          }
    }
    else
    {
        qDebug() << "image not loaded";

    }

        ui->Icon_Table->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->Icon_Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->Icon_Table->show();
}

// ------------------------------------------------------------------------------------
//            Assign Textures From Button Press
// ------------------------------------------------------------------------------------
void MainWindow::setupGameGrid()
{       
    ui->graphicsView->setScene(scene);
    ui->m_FullCameraView->setScene(scene);

    m_mapTable = new QTableWidget;
    m_mapTable->horizontalHeader()->hide();
    m_mapTable->horizontalHeader()->setDefaultSectionSize(50);
    m_mapTable->verticalHeader()->hide();
    m_mapTable->verticalHeader()->setDefaultSectionSize(50);

    m_mapTable->setRowCount(20);
    m_mapTable->setColumnCount(32);

        for (int r = 0; r < m_mapTable->rowCount(); r++)
           {
               for (int c = 0; c < m_mapTable->columnCount(); c++)
                {

                    TileItem* item = new TileItem;
                    item->setData(Qt::UserRole, "Transparent");
                    item->setData(Qt::UserRole+1, QVector2D(c*50, r*50));
                    m_mapTable->setItem(r,c,item);
                }
          }

    m_mapTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_mapTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mapTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_mapTable->setFixedSize(m_mapTable->horizontalHeader()->length()+m_mapTable->verticalHeader()->width(), m_mapTable->verticalHeader()->length()+m_mapTable->horizontalHeader()->height());
    m_proxyWidget = scene->addWidget( m_mapTable );
    ui->graphicsView->scale(0.5,0.5);
    ui->m_FullCameraView->scale(0.1,0.1);
}

void MainWindow::wheelEvent(QWheelEvent *t_event)
{
    if(t_event->delta() > 0)
    {
         ui->graphicsView->scale(1.25, 1.25);
    }
          else
    {
          ui->graphicsView->scale(0.8, 0.8);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *t_event)
{
    if(t_event->key() == Qt::Key_W)
    {
       m_proxyWidget->moveBy(0,10);
    }

    if(t_event->key() == Qt::Key_S)
    {
       m_proxyWidget->moveBy(0,-10);
    }

    if(t_event->key() == Qt::Key_A)
    {
       m_proxyWidget->moveBy(10,0);
    }

    if(t_event->key() == Qt::Key_D)
    {
        m_proxyWidget->moveBy(-10,0);
    }

    if(t_event->key() == Qt::Key_Q)
    {
         ui->graphicsView->scale(1.25, 1.25);
    }
    if(t_event->key() == Qt::Key_E)
    {
          ui->graphicsView->scale(0.8, 0.8);
    }
}


