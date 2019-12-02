#include <QtWidgets>

#include "mainwindow.h"
#include "commands.h"
#include "diagramitem.h"
#include "diagramscene.h"

MainWindow::MainWindow()
{
    undoStack = new QUndoStack(this);

    createActions();
    createMenus();

    createUndoView();

    diagramScene = new DiagramScene();
    QBrush pixMapBrush(QPixmap(":/images/cross.png").scaled(30,30));
    diagramScene->setBackgroundBrush(pixMapBrush);
    diagramScene->setSceneRect(QRect(0,0,500,500));

    connect(diagramScene, &DiagramScene::itemMoved, this, &MainWindow::itemMoved);

    setWindowTitle("Undo FrameWork test");
    QGraphicsView *view = new QGraphicsView(diagramScene);
    setCentralWidget(view);
    resize(700,500);

}

MainWindow::~MainWindow()
{
}

void MainWindow::createUndoView()
{
    undoView = new QUndoView(undoStack);
    undoView->setWindowTitle(tr("Command List"));
    undoView->show();
    undoView->setAttribute(Qt::WA_QuitOnClose, false);
}

void MainWindow::createActions()
{
    deleteAction = new QAction(tr("&Delete Item"), this);
    deleteAction->setShortcut(tr("Del"));
    connect(deleteAction, &QAction::triggered, this, &MainWindow::deleteItem);

    addBoxAction = new QAction(tr("Add &Box"), this);
    addBoxAction->setShortcut(tr("CTRL+O"));
    connect(addBoxAction, &QAction::triggered, this, &MainWindow::addBox);

    addTriangleAction = new QAction(tr("add &Triangle"), this);
    addTriangleAction->setShortcut(tr("CTRL+T"));
    connect(addTriangleAction, &QAction::triggered, this, &MainWindow::addTriangle);

    undoAction = undoStack->createUndoAction(this,tr("&Undo"));
    undoAction->setShortcut(QKeySequence::Undo);

    redoAction = undoStack->createRedoAction(this,tr("&Redo"));
    redoAction->setShortcut(QKeySequence::Redo);

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitAction);

    aboutAction = new QAction(tr("&About"), this);
    QList<QKeySequence> aboutShortcuts;
    aboutShortcuts << tr("CTRL+A") << tr("CTRL+B");
    aboutAction->setShortcuts(aboutShortcuts);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);

}


void MainWindow::createMenus()
{
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);
    editMenu->addSeparator();
    editMenu->addAction(deleteAction);
    connect(editMenu, &QMenu::aboutToShow, this, &MainWindow::itemMenuAboutToShow);
    connect(editMenu, &QMenu::aboutToHide,this, &MainWindow::itemMenuAboutToHide);

}

void MainWindow::itemMoved(DiagramItem *movedItem, const QPointF &oldPosition)
{
    undoStack->push(new MoveCommand(movedItem, oldPosition));
}

void MainWindow::deleteItem()
{
    if(diagramScene->selectedItems().isEmpty())
    {
        return;
    }

    QUndoCommand *deleteCommand = new DeleteCommand(diagramScene);
    undoStack->push(deleteCommand);
}

void MainWindow::itemMenuAboutToHide()
{
    deleteAction->setEnabled(true);
}

void MainWindow::itemMenuAboutToShow()
{
    deleteAction->setEnabled(!diagramScene->selectedItems().isEmpty());
}

void MainWindow::addBox()
{
    QUndoCommand *addCommand = new AddCommand(DiagramItem::Box, diagramScene);
    undoStack->push(addCommand);
}

void MainWindow::addTriangle()
{
    QUndoCommand *addCommand = new AddCommand(DiagramItem::Triangle,diagramScene);
    undoStack->push(addCommand);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Undo"), tr("This is how to Use the Undo Framework"));
}
