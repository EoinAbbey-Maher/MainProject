#include "tile.h"

Tile::Tile(const QColor &t_Color, int t_x, int t_y) :
    m_x(t_x),
    m_y(t_y),
    m_color(t_Color)
{
    setZValue((m_x + m_y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);

}

QRectF Tile::boundingRect() const
{
    return QRectF(0,0,50,50);
}

QPainterPath Tile::shape() const
{
    QPainterPath path;
    path.addRect(14,14,82,42);
    return path;
}

void Tile::paint(QPainter *t_painter, const QStyleOptionGraphicsItem *t_option, QWidget *t_widget)
{
    Q_UNUSED(t_widget);

    QColor fillColor = (t_option->state & QStyle::State_Selected) ? m_color.darker(150) : m_color;
    if(t_option->state &QStyle::State_MouseOver)
    {
        fillColor = fillColor.lighter(125);
    }

    const qreal lod = t_option->levelOfDetailFromTransform(t_painter->worldTransform());
    if(lod < 0.2)
    {
        if(lod < 0.125){
            t_painter->fillRect(QRectF(0,0,50,50), fillColor);
            return;
        }

        QBrush b = t_painter->brush();
        t_painter->setBrush(fillColor);
        t_painter->drawRect(13,13,97,57);
        t_painter->setBrush(b);
        return;
    }

    QPen oldPen = t_painter->pen();
    QPen pen = oldPen;

    int width = 0;
    if(t_option->state & QStyle::State_Selected)
    {
        width += 2;
    }

    pen.setWidth(width);

    QBrush b = t_painter->brush();
    t_painter->setBrush(QBrush(fillColor.darker(t_option->state & QStyle::State_Sunken ? 120 : 100)));

    t_painter->drawRect(QRect(14,14,79,39));
    t_painter->setBrush(b);

    if(lod >=1)
    {
        t_painter->setPen(QPen(Qt::gray,1));
        t_painter->drawLine(15,54,94,54);
        t_painter->drawLine(94,53,94,15);
        t_painter->setPen(QPen(Qt::black, 0));

    }
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Tile::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->modifiers() & Qt::ShiftModifier)
    {
        m_pointVectors << event->pos();
        update();
        return;
    }

    QGraphicsItem::mouseMoveEvent(event);

}

void Tile::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
