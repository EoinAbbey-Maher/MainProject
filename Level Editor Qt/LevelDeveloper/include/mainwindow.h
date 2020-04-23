#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QtWidgets"
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QTableWidget>

#include "tileitem.h"
#include "xmlwriter.h"

#include "startingscreen.h"
#include "newtilewindow.h"
#include "maplayoutscreen.h"

class StartingScreen;
class MapLayoutScreen;
class XMLWriter;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int t_tableHeight = 0, int t_tableWidth = 0, QWidget *parent = nullptr);
    ~MainWindow();

public:
    Ui::MainWindow *ui;

    QTableWidget * m_mapTable;
    QTableWidget * m_NodeTable;
    QVector<QPair<QString, QString>> m_texturePair;

    QTableWidget * m_activeTable;

signals:

private slots:
    void handleApplyButton();
    void handleClearButton();
    void handleExportButton();
    void handleTableChange();
    void wheelEvent(QWheelEvent *t_event);
    void keyPressEvent(QKeyEvent * t_event);

    void addRow();
    void addColumn();
    void open();
    void newMap();
    void closeProgram();
    void openNewTile();
    void returnToMain();
    void saveReturnToMain();


private: //variables
    QGraphicsScene * scene = new QGraphicsScene(this);
    QGraphicsProxyWidget * m_proxyWidget = new QGraphicsProxyWidget;

    QAction *setTextureAction;
    QAction *removeTextureAction;
    QAction *undoAction;
    QAction * redoAction;
    QAction * saveAsAct;
    QAction * newMapAct;
    QAction * returnToMainAct;
    QAction * saveandReturnAct;
    QAction * closeMapAction;
    QAction * OpenMapAct;
    QAction * openTile;

    QAction * addColAct;
    QAction * addRowAct;

    QUndoStack *undoStack;

    XMLWriter* m_xmlWriter = new XMLWriter;

    QVector<TileItem> m_mapTiles;
    QVector<TileItem> m_iconTiles;

    QVector<QString> m_TexturePaths;

    QPoint m_tileSize = QPoint(50,50);

    QPoint m_gameGridSize = QPoint(32,20);

    NewTileWindow* m_newTileWindow;
    StartingScreen * m_StartScreen;
    MapLayoutScreen * m_MapLayoutScreen;

private: //functions

    static void initImageFileDialog(QFileDialog& t_dialog, QFileDialog::AcceptMode t_accept);

    void createMenus();
    void createActions();

    void setTextures();
    void removeTextures();
    void setupIcons();
    void setupGameGrid(int t_height, int t_width);

    bool SaveFile();

    void resizeTables();

};
#endif // MAINWINDOW_H
