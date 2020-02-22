#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QtWidgets"
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QTableWidget>

#include "tileitem.h"
#include "mygraphicsview.h"
#include "xmlwriter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
signals:



private slots:
    void handleApplyButton();
    void handleClearButton();
    void handleExportButton();
    void wheelEvent(QWheelEvent *t_event);
    void keyPressEvent(QKeyEvent * t_event);

    void open();
    void newMap();


private: //variables
    QGraphicsScene * scene = new QGraphicsScene(this);
    QGraphicsProxyWidget * m_proxyWidget = new QGraphicsProxyWidget;

    Ui::MainWindow *ui;

    QAction *setTextureAction;
    QAction *removeTextureAction;
    QAction *undoAction;
    QAction * redoAction;
    QAction * saveAsAct;
    QAction * newMapAct;

    QUndoStack *undoStack;

    XMLWriter m_xmlWriter;

    QVector<TileItem> m_mapTiles;
    QVector<TileItem> m_iconTiles;

    QVector<QString> m_TexturePaths;

    QTableWidget * m_mapTable;


private: //functions


    void createMenus();
    void createActions();

    void setTextures();
    void removeTextures();
    void setupIcons();
    void setupGameGrid();

    bool SaveFile();

};
#endif // MAINWINDOW_H
