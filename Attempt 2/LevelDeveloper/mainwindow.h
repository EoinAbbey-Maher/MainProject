#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QtWidgets"
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QTableWidget>

#include "mygraphicsview.h"

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
    void wheelEvent(QWheelEvent *t_event);
    void keyPressEvent(QKeyEvent * t_event);

private: //variables
    QGraphicsScene * scene = new QGraphicsScene(this);
    QGraphicsProxyWidget * m_proxyWidget = new QGraphicsProxyWidget;

    Ui::MainWindow *ui;

    QAction *setTextureAction;
    QAction *removeTextureAction;
    QAction *undoAction;
    QAction * redoAction;

    QUndoStack *undoStack;

private: //functions

    QTableWidget * m_mapTable;

    void createActions();

    void setTextures();
    void removeTextures();
    void setupIcons();
    void setupGameGrid();

};
#endif // MAINWINDOW_H
