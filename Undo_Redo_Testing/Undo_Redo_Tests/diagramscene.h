#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include <diagramitem.h>


class DiagramItem;
QT_BEGIN_NAMESPACE
class QGraphicsSceneDragDropEvent;
class QGraphicViewItem;
QT_END_NAMESPACE;

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    DiagramScene(QObject *parent = 0);

signals:
    void itemMoved(DiagramItem *movedItem, const QPointF *MovedFromPositon);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsItem *movingItem;
    QPointF oldPos;
};

#endif // DIAGRAMSCENE_H
