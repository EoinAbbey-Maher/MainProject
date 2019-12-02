#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUndoCommand>
#include <QUndoView>
#include <QUndoStack>
#include <QMessageBox>

#include "diagramitem.h"
#include "diagramscene.h"

QT_BEGIN_NAMESPACE
class QAction;
class QToolBar;
class QMenu;
class QUndoStack;
class QUndoView;
QT_END_NAMESPACE

class DiagramScene;
class DiagramItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow();
    ~MainWindow();

public slots:
    void itemMoved(DiagramItem *movedDiagram, const QPointF &moveStartPos);

private slots:
    void deleteItem();
    void addBox();
    void addTriangle();
    void about();
    void itemMenuAboutToShow();
    void itemMenuAboutToHide();

private:
    void createActions();
    void createMenus();
    void createUndoView();

QAction *deleteAction;
QAction *addBoxAction;
QAction *addTriangleAction;
QAction *undoAction;
QAction *redoAction;
QAction *exitAction;
QAction *aboutAction;

QMenu *fileMenu;
QMenu *editMenu;
QMenu *itemMenu;
QMenu *helpMenu;

DiagramScene *diagramScene;
QUndoStack *undoStack;
QUndoView *undoView;


};


#endif // MAINWINDOW_H
