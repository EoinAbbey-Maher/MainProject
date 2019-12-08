#ifndef TILE_H
#define TILE_H

#include <QGraphicsItem>
#include <QColor>

#include <QtWidgets>

class Tile : public QGraphicsItem
{
public:
    Tile(const QColor& Color, int t_x, int t_y);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int m_x;
    int m_y;
    QColor m_color;
    QVector<QPointF> m_pointVectors;

};

#endif // TILE_H
