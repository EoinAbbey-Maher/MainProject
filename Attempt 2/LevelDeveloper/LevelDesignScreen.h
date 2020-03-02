#ifndef LEVELDESIGNSCREEN_H
#define LEVELDESIGNSCREEN_H


#include "QtWidgets"
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QTableWidget>

#include "tileitem.h"
#include "mygraphicsview.h"
#include "xmlwriter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LevelDesignScreen; }
QT_END_NAMESPACE

class LevelDesignScreen : public QDialog
{
    Q_OBJECT

public:
    LevelDesignScreen(QWidget *parent = nullptr);
    ~LevelDesignScreen();

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

    Ui::LevelDesignScreen *ui;

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
