#include "DragWidget.h"
#include <QtWidgets>

DragWidget::DragWidget(QWidget *parent) : QFrame(parent)
{
    setMinimumSize(800,800);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAcceptDrops(true);

    QLabel*FloorIcon = new QLabel(this);
    FloorIcon->setPixmap(QPixmap(":/Images/floor.jpg"));
    FloorIcon->move(10,10);
    FloorIcon->show();
    FloorIcon->setAttribute(Qt::WA_DeleteOnClose);

}

void DragWidget::dragEnterEvent(QDragEnterEvent * event)
{
    if(event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if(event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->acceptProposedAction();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
}

void DragWidget::dragMoveEvent(QDragMoveEvent * event)
{
    if(event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        if(event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->acceptProposedAction();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }

}

void DragWidget::dropEvent(QDropEvent * event)
{

    if(event->mimeData()->hasFormat("application/x-dnditemdata"))
    {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream datastream(&itemData, QIODevice::ReadOnly);

        QPixmap pixmap;
        QPoint offset;
        datastream>>pixmap >> offset;

        QLabel* newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);

        if(event->source() == this)
        {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        }
        else
        {
            event->acceptProposedAction();
        }
    }
    else
    {
        event->ignore();
    }
}

void DragWidget::mousePressEvent(QMouseEvent *event)
{
    QLabel *child = static_cast<QLabel*>(childAt((event->pos())));
    if(!child)
    {
        return;
    }

    QPixmap pixmap =*child->pixmap();

    QByteArray itemData;
    QDataStream datastream(&itemData, QIODevice::WriteOnly);
    datastream << pixmap << QPoint(event->pos() - child->pos());


    QMimeData * mimeData = new QMimeData;
    mimeData->setData("application/x-dnditemdata", itemData);


    QDrag * drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127,127,127,127));
    painter.end();

    child->setPixmap(tempPixmap);

    if(drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
    {
child->close();
    }
    else
    {
        child->show();
        child->setPixmap(pixmap);
    }



}
