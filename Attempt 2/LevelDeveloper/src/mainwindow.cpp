#include "include/mainwindow.h"
#include "ui_mainwindow.h"


#include <QMenu>
#include <QMenuBar>
#include <QClipboard>
#include <QImageReader>
#include <QImageWriter>
#include <QMimeData>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDir>
#include <QApplication>

// ------------------------------------------------------------------------------------
//            Constructor with Height and Width input
// ------------------------------------------------------------------------------------
MainWindow::MainWindow(int t_tableHeight, int t_tableWidth, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setStyleSheet("QTableWidget {background-color: transparent;}"
                  "QHeaderView::section {background-color: transparent;}"
                  "QHeaderView {background-color: transparent;}"
                  "QTableCornerButton::section {background-color: transparent;}");
    this->setStyleSheet("background-color: darkgrey;");

    this->setAttribute(Qt::WA_AlwaysShowToolTips, true);
    this->setWindowTitle("Jigsaw Tiled Map Designer");
    m_gameGridSize.setX(t_tableWidth);
    m_gameGridSize.setY(t_tableHeight);

    ui->setupUi(this);

    createMenus();

    m_texturePair.push_back(QPair<QString,QString>(":/floor.png", "floor"));
    m_texturePair.push_back(QPair<QString,QString>(":/floor1.png", "floor1"));
    m_texturePair.push_back(QPair<QString,QString>(":/floor2.png", "floor2"));
    m_texturePair.push_back(QPair<QString,QString>(":/floor3.png", "floor3"));
    m_texturePair.push_back(QPair<QString,QString>(":/empty.png", "empty"));
    m_texturePair.push_back(QPair<QString,QString>(":/playerNode", "playerNode"));
    m_texturePair.push_back(QPair<QString,QString>(":/NPCNode", "NPCNode"));

    setupIcons();
    setupGameGrid(m_gameGridSize.y(), m_gameGridSize.x());

    m_activeTable = m_mapTable;

    connect(ui->m_applyButton, SIGNAL(released()), this,SLOT(handleApplyButton()));
    connect(ui->m_clearCellButton, SIGNAL(released()),this,SLOT(handleClearButton()));
    connect(ui->m_exportButton, SIGNAL(released()), this, SLOT(handleExportButton()));

    connect(ui->Icon_Table, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));
    connect(m_mapTable, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));
    connect(m_NodeTable, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));
    connect(m_activeTable, SIGNAL(cellDoubleClicked(int,int)), this,SLOT(handleApplyButton()));

    connect(ui->m_layerCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(handleTableChange()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


// ------------------------------------------------------------------------------------
//                          Handle Apply Button Press
// ------------------------------------------------------------------------------------
void MainWindow::handleApplyButton()
{
    //ui->m_applyButton->setText("Pressed");
if( m_mapTable->selectedItems().size() != 0 && ui->Icon_Table->selectedItems().size() != 0)
{
    setTextures();
}

}

// ------------------------------------------------------------------------------------
//                  clear the tile
// ------------------------------------------------------------------------------------
void MainWindow::handleClearButton()
{
    if(m_mapTable->selectedItems().size() != 0)
    {
        removeTextures();
    }
}

// ------------------------------------------------------------------------------------
//                      Handle File Export
// ------------------------------------------------------------------------------------
void MainWindow::handleExportButton()
{
    m_xmlWriter->WriteTilesToFile(m_mapTable, m_texturePair);
}


// ------------------------------------------------------------------------------------
//                      Handle layer Change
// ------------------------------------------------------------------------------------
void MainWindow::handleTableChange()
{
    switch(ui->m_layerCombo->currentIndex())
    {
    case 0:
        m_activeTable = m_mapTable;
        break;

    case 1:
        m_activeTable = m_NodeTable;
        break;

    default:
        break;
    }
    m_activeTable->setFocus();
}

// ------------------------------------------------------------------------------------
//            Create Action Buttons
// ------------------------------------------------------------------------------------
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
    if( ui->Icon_Table->selectedItems().at(0)->data(Qt::UserRole+3) != "Node")
    {
        for (int i = 0; i <  m_mapTable->selectedItems().count(); i++)
        {
            m_mapTable->selectedItems().at(i)->setData(Qt::DecorationRole, ui->Icon_Table->selectedItems().at(0)->data(Qt::DecorationRole).value<QPixmap>());
            m_mapTable->selectedItems().at(i)->setData(Qt::UserRole, ui->Icon_Table->selectedItems().at(0)->data(Qt::UserRole));
        }
    }
    else
    {
        for (int i = 0; i <  m_NodeTable->selectedItems().count(); i++)
        {
            m_NodeTable->selectedItems().at(i)->setData(Qt::DecorationRole, ui->Icon_Table->selectedItems().at(0)->data(Qt::DecorationRole).value<QPixmap>());
            m_NodeTable->selectedItems().at(i)->setData(Qt::UserRole, ui->Icon_Table->selectedItems().at(0)->data(Qt::UserRole));
        }
    }
    qDebug() << "setup Textures";
}

// ------------------------------------------------------------------------------------
//            Remove Texture From Cell
// ------------------------------------------------------------------------------------
void MainWindow::removeTextures()
{
    QString imgString = "empty";
    QImage *emptyImg = new QImage();

    for (int i = 0; i <  m_activeTable->selectedItems().count(); i++)
    {
        m_activeTable->selectedItems().at(i)->setData(Qt::DecorationRole, QPixmap::fromImage(*emptyImg));
        m_activeTable->selectedItems().at(i)->setData(Qt::UserRole, m_texturePair[4].second);
    }
}

// ------------------------------------------------------------------------------------
//            initial setup Of Icon Table
// ------------------------------------------------------------------------------------
void MainWindow::setupIcons()
{

    QImage *img = new QImage();
    bool loaded = img->load(m_texturePair[0].first);
    img->scaled(m_tileSize.x(),m_tileSize.y()  , Qt::KeepAspectRatio);

    QImage *img1= new QImage();
    img1->load(m_texturePair[1].first);
    img1->scaled(m_tileSize.x(),m_tileSize.y(), Qt::KeepAspectRatio);

    QImage *img2= new QImage();
    img2->load(m_texturePair[2].first);

    img2->scaled(m_tileSize.x(),m_tileSize.y(), Qt::KeepAspectRatio);

    QImage *img3= new QImage();
    img3->load(m_texturePair[3].first);
    img3->scaled(m_tileSize.x(),m_tileSize.y(), Qt::KeepAspectRatio);

    QImage *img4= new QImage();
    img4->load(m_texturePair[4].first);
    img4->scaled(m_tileSize.x(),m_tileSize.y(), Qt::KeepAspectRatio);

    QImage *playerNode = new QImage();
    playerNode->load(m_texturePair[5].first);

    QImage *NPCNode = new QImage();
    NPCNode->load(m_texturePair[6].first);


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
                                item->setData(Qt::UserRole,m_texturePair[0].second);
                                item->setData(Qt::UserRole+3, "Floor");
                                item->setIndexVal(QVector2D(r,c));
                                item->setToolTip("Name: " + m_texturePair[0].second + "\nType: Floor");
                                ui->Icon_Table->setItem(r,c,item);
                                    break;
                        case 1:
                                item->setTexture(img1);
                                item->setData(Qt::UserRole,m_texturePair[1].second);
                                item->setData(Qt::UserRole+3, "Floor");
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img1));
                                item->setIndexVal(QVector2D(r,c));
                                item->setToolTip("Name: " + m_texturePair[1].second + "\nType: Floor");
                                ui->Icon_Table ->setItem(r,c,item);
                                    break;
                        case 2:
                                item->setTexture(img2);
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img2));
                                item->setData(Qt::UserRole+3, "Floor");
                                item->setData(Qt::UserRole, m_texturePair[2].second);
                                item->setIndexVal(QVector2D(r,c));
                                item->setToolTip("Name: " + m_texturePair[2].second + "\nType: Floor");
                                ui->Icon_Table ->setItem(r,c,item);
                                    break;
                        case 3:
                                item->setTexture(img3);
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(*img3));
                                item->setData(Qt::UserRole+3, "Floor");
                                item->setData(Qt::UserRole,m_texturePair[3].second);
                                item->setIndexVal(QVector2D(r,c));
                                item->setToolTip("Name: " + m_texturePair[3].second + "\nType: Floor");
                                ui->Icon_Table ->setItem(r,c,item);
                                break;

                        case 4:
                                item->setTexture(playerNode);
                                item->setData(Qt::DecorationRole, QPixmap::fromImage(playerNode->scaled(m_tileSize.x(), m_tileSize.y())));
                                item->setData(Qt::UserRole+3, "Node");
                            item->setData(Qt::UserRole,m_texturePair[5].second);
                            item->setIndexVal(QVector2D(r,c));
                            item->setToolTip("Name: " + m_texturePair[5].second + "\nType: Node");
                            ui->Icon_Table ->setItem(r,c,item);
                            break;

                        case 5:
                            item->setTexture(NPCNode);
                            item->setData(Qt::DecorationRole, QPixmap::fromImage(NPCNode->scaled(m_tileSize.x(), m_tileSize.y())));
                            item->setData(Qt::UserRole+3, "Node");
                            item->setData(Qt::UserRole,m_texturePair[6].second);
                            item->setIndexVal(QVector2D(r,c));
                            item->setToolTip("Name: " + m_texturePair[6].second + "\nType: Node");
                            ui->Icon_Table ->setItem(r,c,item);
                            break;

                        default: break;
                        }
                        break;

                    default:
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
//            Game Grid Setup With Give Width and height
// ------------------------------------------------------------------------------------
void MainWindow::setupGameGrid(int t_height = 10, int t_width = 10)
{
    //Setup Main Game Table
    ui->graphicsView->setScene(scene);
    ui->m_FullCameraView->setScene(scene);

    m_mapTable = new QTableWidget;
    m_mapTable->horizontalHeader()->hide();
    m_mapTable->horizontalHeader()->setDefaultSectionSize(m_tileSize.x());
    m_mapTable->verticalHeader()->hide();
    m_mapTable->verticalHeader()->setDefaultSectionSize(m_tileSize.y());

    m_mapTable->setRowCount(t_height);
    m_mapTable->setColumnCount(t_width);

        for (int r = 0; r < m_mapTable->rowCount(); r++)
           {
               for (int c = 0; c < m_mapTable->columnCount(); c++)
                {

                    TileItem* item = new TileItem;
                    item->setData(Qt::UserRole, "empty");
                    item->setData(Qt::UserRole+1, QString::number(c * m_tileSize.x()));
                    item->setData(Qt::UserRole+2, QString::number(r * m_tileSize.y()));
                    item->setData(Qt::UserRole+3, "empty");
                    m_mapTable->setItem(r,c,item);
                }
          }

    m_mapTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_mapTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_mapTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_mapTable->setFixedSize(m_mapTable->horizontalHeader()->length()+m_mapTable->verticalHeader()->width(), m_mapTable->verticalHeader()->length()+m_mapTable->horizontalHeader()->height());
    m_proxyWidget = scene->addWidget( m_mapTable );

    //Setup Node Table;
    m_NodeTable = new QTableWidget;
    m_NodeTable->horizontalHeader()->hide();
    m_NodeTable->horizontalHeader()->setDefaultSectionSize(m_tileSize.x());
    m_NodeTable->verticalHeader()->hide();
    m_NodeTable->verticalHeader()->setDefaultSectionSize(m_tileSize.y());

    m_NodeTable->setRowCount(t_height);
    m_NodeTable->setColumnCount(t_width);



    for (int r = 0; r < m_NodeTable->rowCount(); r++)
       {
           for (int c = 0; c < m_NodeTable->columnCount(); c++)
            {

                TileItem* item = new TileItem;
                item->setData(Qt::UserRole, "empty");
                item->setData(Qt::UserRole+1, QString::number(c * m_tileSize.x()));
                item->setData(Qt::UserRole+2, QString::number(r * m_tileSize.y()));
                item->setData(Qt::UserRole+3, "Node");
                m_NodeTable->setItem(r,c,item);
            }
      }

    m_NodeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_NodeTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_NodeTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_NodeTable->setFixedSize(m_NodeTable->horizontalHeader()->length()+m_NodeTable->verticalHeader()->width(), m_NodeTable->verticalHeader()->length()+m_NodeTable->horizontalHeader()->height());

     m_proxyWidget = scene->addWidget( m_NodeTable );

    double tableWidth = m_mapTable->columnCount();
    double tableHeight = m_mapTable->rowCount();

    ui->m_FullCameraView->setSceneRect(0,0,tableWidth * m_tileSize.x(), tableHeight*m_tileSize.y());
    ui->m_FullCameraView->fitInView(0,0,tableWidth * m_tileSize.x(), tableHeight* m_tileSize.y(),Qt::KeepAspectRatio);

    ui->m_FullCameraView->scale(5,5);
}



// ------------------------------------------------------------------------------------
//            Zoom In And Out On Mouse Wheel Roll
// ------------------------------------------------------------------------------------
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


// ------------------------------------------------------------------------------------
//            Move Up Down Left And Right based on W A S D input
// ------------------------------------------------------------------------------------
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

// ------------------------------------------------------------------------------------
//              Add New Row To The Table
// ------------------------------------------------------------------------------------
void MainWindow::addRow()
{
    m_mapTable->insertRow(1);
    m_gameGridSize.ry()++;
}

// ------------------------------------------------------------------------------------
//              Add New Column To The Table
// ------------------------------------------------------------------------------------
void MainWindow::addColumn()
{
    m_mapTable->insertColumn(1);
    m_gameGridSize.rx()++;
}



// ------------------------------------------------------------------------------------
//            Open And load Existing XML Map File
// ------------------------------------------------------------------------------------
void MainWindow::open()
{
    close();
    m_xmlWriter->ReadExistingFile();
}

// ------------------------------------------------------------------------------------
//                  Function to create new map
// ------------------------------------------------------------------------------------
void MainWindow::newMap()
{
    m_mapTable->clear();

    m_MapLayoutScreen = new MapLayoutScreen;

    close();
    m_MapLayoutScreen->show();

}

// ------------------------------------------------------------------------------------
//            Button Response to shutdown complete program
// ------------------------------------------------------------------------------------
void MainWindow::closeProgram()
{
    close();
}

// ------------------------------------------------------------------------------------
//            Open Page to make New Tile
// ------------------------------------------------------------------------------------
void MainWindow::openNewTile()
{
    m_newTileWindow = new NewTileWindow(m_texturePair, *ui->Icon_Table);

    m_newTileWindow->show();
    m_newTileWindow->activateWindow();
    m_newTileWindow->raise();
}

// ------------------------------------------------------------------------------------
//                      Return back to the Main Menu
// ------------------------------------------------------------------------------------
void MainWindow::returnToMain()
{
    m_StartScreen = new StartingScreen;
    m_StartScreen->show();
    close();

}

// ------------------------------------------------------------------------------------
//              Save Map and return to the main menu
// ------------------------------------------------------------------------------------
void MainWindow::saveReturnToMain()
{
    handleExportButton();
    returnToMain();
}

// ------------------------------------------------------------------------------------
//            Create MenuBar Options and Connections
// ------------------------------------------------------------------------------------
void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    OpenMapAct = fileMenu->addAction(tr("&Open existing Project"), this, &MainWindow::open);
    OpenMapAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("&Export Map"), this, &MainWindow::handleExportButton);
    saveAsAct->setShortcut(QKeySequence::Save);

    newMapAct = fileMenu->addAction(tr("&New Map"), this,&MainWindow::newMap);

    saveandReturnAct = fileMenu->addAction(tr("&Save and Return to Main Menu"), this, &MainWindow::saveReturnToMain);

    returnToMainAct = fileMenu->addAction(tr("&Return to Main Menu"), this, &MainWindow::returnToMain);

    closeMapAction = fileMenu->addAction(tr("&Quit Program"), this, &MainWindow::closeProgram);

    fileMenu->addSeparator();

    QMenu * addMenu = menuBar()->addMenu(tr("&Add"));
    openTile = addMenu->addAction(tr("&Add New Tile"), this, &MainWindow::openNewTile);

    addColAct = addMenu->addAction(tr("&Add A Column"), this, &MainWindow::addColumn);
    addRowAct = addMenu->addAction(tr("Add A Row"), this, &MainWindow::addRow);
    addMenu->addSeparator();

}
