#include "include\mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget *parent):
    QGraphicsView(parent)
{

}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double  Scalar = 1;
    if(event->delta() > 0)
    {
        scale(Scalar, Scalar);
    }
    else
    {
        scale(1.0/Scalar, 1.0 / Scalar);
    }
}

