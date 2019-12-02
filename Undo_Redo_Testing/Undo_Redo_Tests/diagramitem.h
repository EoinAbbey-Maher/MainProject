#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QGraphicsPolygonItem>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMoveEvent;
class QPointF;
QT_END_NAMESPACE

class DiagramItem : public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 1 };
    enum DiagramType { Box, Triangle };

    explicit DiagramItem(DiagramType diagramType, QGraphicsItem *item = nullptr);

    DiagramType diagramType() const {
        return polygon() == boxPolygon ? Box : Triangle;
    }
    int type() const override { return Type; }

private:
    QPolygonF boxPolygon;
    QPolygonF trianglePolygon;
};

#endif // DIAGRAMITEM_H
