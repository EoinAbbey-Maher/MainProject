/**
*    mainWindow.h
*    @author Eoin Abbey-Maher
*    @brief Setup and Variables of the main Application window where tiles can be set
*/

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
    /**
     * @brief Constructor for the MainWindow
     * @param t_tableHeight Custom Height parameter for the table
     * @param t_tableWidth Custom Width parameter for the table
     */
    MainWindow(int t_tableHeight = 0, int t_tableWidth = 0, QWidget *parent = nullptr);
    ~MainWindow();

public:
    Ui::MainWindow *m_ui;

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
    void removeRow();
    void removeCol();

    void open();
    void newMap();
    void closeProgram();
    void openNewTile();
    void returnToMain();
    void saveReturnToMain();


private: //variables
    QGraphicsScene * m_scene= new QGraphicsScene(this);
    QGraphicsProxyWidget * m_proxyWidget = new QGraphicsProxyWidget;

    QAction * m_setTextureAct;
    QAction * m_removeTextureAct;
    QAction * m_saveAsAct;
    QAction * m_newMapAct;
    QAction * m_returnToMainAct;
    QAction * m_saveandReturnAct;
    QAction * m_closeMapAction;
    QAction * m_openMapAct;
    QAction * m_openTileAct;

    QAction * m_addColAct;
    QAction * m_addRowAct;
    QAction * m_removeRowAct;
    QAction * m_removeColAct;

    XMLWriter* m_xmlWriter = new XMLWriter;

    QVector<TileItem> m_mapTiles;
    QVector<TileItem> m_iconTiles;

    QVector<QString> m_texturePaths;

    QPoint m_tileSize = QPoint(50,50);

    QPoint m_gameGridSize = QPoint(32,20);

    NewTileWindow * m_newTileWindow;
    StartingScreen * m_StartScreen;
    MapLayoutScreen * m_MapLayoutScreen;

private: //functions

    void createMenus();
    void createActions();

    void setTextures();
    void removeTextures();
    void setupIcons();
    void setupGameGrid(int t_height, int t_width);

    bool saveFile();

    void resizeTables();

};
#endif // MAINWINDOW_H
