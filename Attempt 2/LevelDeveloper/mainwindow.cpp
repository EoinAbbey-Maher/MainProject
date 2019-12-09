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

    ui->graphicsView->setScene(scene);

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

                    QTableWidgetItem * item = new QTableWidgetItem;
                    m_mapTable->setItem(r,c,item);
                }
          }

    m_mapTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_mapTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mapTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_mapTable->setFixedSize(m_mapTable->horizontalHeader()->length()+m_mapTable->verticalHeader()->width(), m_mapTable->verticalHeader()->length()+m_mapTable->horizontalHeader()->height());
    m_proxyWidget = scene->addWidget( m_mapTable );
    ui->graphicsView->scale(0.5,0.5);
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
       m_proxyWidget->moveBy(0,5);
    }

    if(t_event->key() == Qt::Key_S)
    {
       m_proxyWidget->moveBy(0,-5);
    }

    if(t_event->key() == Qt::Key_A)
    {
       m_proxyWidget->moveBy(5,0);
    }

    if(t_event->key() == Qt::Key_D)
    {
        m_proxyWidget->moveBy(-5,0);
    }

}


