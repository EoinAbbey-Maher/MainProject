#include "mygraphicsview.h"


#if QT_CONFIG(wheelevent)
void MyGraphicsView::wheelEvent(QWheelEvent *t_event)
{
    if(t_event->modifiers() & Qt::ControlModifier)
    {
        if(t_event->delta() > 0)
        {
            m_view->zoomIn(6);
        }
        else
        {
            m_view->zoomOut(6);
        }
    }
    else
    {
        QGraphicsView::wheelEvent(t_event);
    }
}
#endif


View::View(const QString &t_name, QWidget *t_parent)
    :QFrame(t_parent)
{
    setFrameStyle(Sunken | StyledPanel);
    m_graphicsView = new MyGraphicsView(this);
    m_graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSIze(size, size);

    m_zoomSlider = new QSlider;
    m_zoomSlider->setMinimum(0);
    m_zoomSlider->setMaximum(250);
m_zoomSlider->setTickPosition(QSlider::TicksRight);

    setupMatrix();
}

QGraphicsView *View::m_view() const
{
    return static_cast<QGraphicsView *>(m_graphicsView);
}

void View::zoomIn(int t_scale)
{
    m_zoomSlider->setValue(m_zoomSlider->value() + t_scale);
}

void View::zoomOut(int t_scale)
{
    m_zoomSlider->setValue(m_zoomSlider->value() - t_scale);
}

void View::setupMatrix()
{
    qreal scale =qPow(qreal(2), (m_zoomSlider->value() - 250 )/ qreal(50));

    QMatrix matrix;
    matrix.scale(scale,scale);
    m_graphicsView->setMatrix(matrix);

}
