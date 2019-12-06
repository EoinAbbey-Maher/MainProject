#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>


class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(QWidget *parent =0);

signals:
protected :
    void wheelEvent(QWheelEvent *event);
};


#endif // MYGRAPHICSVIEW_H
