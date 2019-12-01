#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    deletAction->setEnabled(true);
}

void MainWindow::itemMenuAboutToShow()
{
    deletAction->setEnabled(!diagramScene->selectedItems().isEmpty());
}

void MainWindow::addBox()
{
    QUndoCommand *addCommand = new addCommand(DiagramItem::Box, diagramScene);
    undoStack->push(addCommand);
}

void MainWindow::addTriangle()
{
    QUndoCommand *addCommand = new AddCommand(DiagramScene::Triangle,diagramScene);
    undoStack->push(addCommand);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Undo"), tr("This is how to Use the Undo Framework"))
}
