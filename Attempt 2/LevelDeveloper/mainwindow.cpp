#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QMenuBar>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: darkgrey;");

    createMenus();

    m_TexturePaths.push_back(":/floor.png");
    m_TexturePaths.push_back(":/floor1.png");
    m_TexturePaths.push_back(":/floor2.png");
    m_TexturePaths.push_back(":/floor3.png");
    m_TexturePaths.push_back(":/empty.png");

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
    m_xmlWriter.WriteTilesToFile(m_mapTable, m_TexturePaths);
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
        m_mapTable->selectedItems().at(i)->setData(Qt::UserRole, m_TexturePaths[4]);
   }

}

// ------------------------------------------------------------------------------------
//            Assign Textures From Button Press
// ------------------------------------------------------------------------------------
void MainWindow::setupIcons()
{

    QImage *img = new QImage();
    bool loaded = img->load(m_TexturePaths[0]);
    img->scaled(50,50, Qt::KeepAspectRatio);

    QImage *img1= new QImage();
    img1->load(m_TexturePaths[1]);
    img1->scaled(50,50, Qt::KeepAspectRatio);

    QImage *img2= new QImage();
    img2->load(m_TexturePaths[2]);

    img2->scaled(50,50, Qt::KeepAspectRatio);

    QImage *img3= new QImage();
    img3->load(m_TexturePaths[3]);
    img3->scaled(50,50, Qt::KeepAspectRatio);

    QImage *img4= new QImage();
    img4->load(m_TexturePaths[4]);
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
                                item->setData(Qt::UserRole,m_TexturePaths[0]);
                                item->setData(Qt::UserRole+3, "Floor");
                                item->setIndexVal(QVector2D(r,c));
                                ui->Icon_Table->setItem(r,c,item);
                                    break;
                        case 1:
                                item->setTexture(img1);
                                item->setData(Qt::UserRole,m_TexturePaths[1]);
                                item->setData(Qt::UserRole+3, "Floor");
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img1));
                                item->setIndexVal(QVector2D(r,c));
                                ui->Icon_Table ->setItem(r,c,item);
                                    break;
                        case 2:
                                item->setTexture(img2);
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img2));
                                item->setData(Qt::UserRole+3, "Floor");
                                item->setData(Qt::UserRole, m_TexturePaths[2]);
                                item->setIndexVal(QVector2D(r,c));
                                ui->Icon_Table ->setItem(r,c,item);
                                    break;
                        case 3:
                                item->setTexture(img3);
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img3));
                                item->setData(Qt::UserRole+3, "Floor");
                                item->setData(Qt::UserRole,m_TexturePaths[3]);
                                item->setIndexVal(QVector2D(r,c));
                                ui->Icon_Table ->setItem(r,c,item);
                                    break;

                        default: break;
                        }
                        break;

                    default:
                        item->setTexture(img);
                        item->setData(Qt::UserRole, m_TexturePaths[4]);
                        item->setData(Qt::UserRole+3, "Floor");
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
                    item->setData(Qt::UserRole, "empty.png");
                    item->setData(Qt::UserRole+1, QString::number(c * 32));
                    item->setData(Qt::UserRole+2, QString::number(r * 32));
                    item->setData(Qt::UserRole+3, "empty");
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

void MainWindow::open()
{

}

void MainWindow::newMap()
{
    m_mapTable->clear();
    setupGameGrid();


}

void MainWindow::closeProgram()
{
    close();
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    OpenMapAct = fileMenu->addAction(tr("&Open..."), this, &MainWindow::open);
    OpenMapAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("&Export Map As..."), this, &MainWindow::handleExportButton);
    saveAsAct->setShortcut(QKeySequence::Save);

    newMapAct = fileMenu->addAction(tr("&New Map"), this,&MainWindow::newMap);

    closeMapAction = fileMenu->addAction(tr("&Quit Program"), this, &MainWindow::closeProgram);

    fileMenu->addSeparator();

}
