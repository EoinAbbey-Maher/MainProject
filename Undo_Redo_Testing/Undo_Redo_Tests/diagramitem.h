
#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPolygonItem>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
class QPointF;
QT_END_NAMESPACE

class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 1 };
    enum DiagramType { Box, Triangle };

    explicit DiagramItem(DiagramType diagramType, QGraphicsItem *item = 0);

    DiagramType diagramType() const {
        return polygon() == boxPolygon ? Box : Triangle;
    }
    int type() const override { return Type; }

private:
    QPolygonF boxPolygon;
    QPolygonF trianglePolygon;
};

#endif
