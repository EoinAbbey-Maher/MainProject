#include "diagramscene.h"
#include "diagramitem.h"

#include <QtWidgets>

DiagramScene::DiagramScene(QObject *parent) :
    QGraphicsScene(parent)
{
    movingItem = 0;
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(),
                       event->buttonDownScenePos(Qt::LeftButton).y());

    const QList<QGraphicsItem *> itemList = items(mousePos);
    movingItem = itemList.empty() ? 0 : itemList.first();

    if(movingItem != 0 && event->button() == Qt::LeftButton)
    {
        oldPos = movingItem->pos();
    }

    clearSelection();
    QGraphicsScene::mousePressEvent(event);

}


void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
if(movingItem != 0 && event->button() == Qt::LeftButton)
    {
        if(oldPos != movingItem->pos())
        {
            emit itemMoved(qgraphicsitem_cast<DiagramItem *>(movingItem), &oldPos);


        }
        movingItem = 0;
    }
    QGraphicsScene::mouseReleaseEvent(event);

}


