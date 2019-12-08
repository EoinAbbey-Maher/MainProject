#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QFrame>

#include <QtWidgets>
#include <qmath.h>

QT_BEGIN_NAMESPACE

class Qlabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

///
/// \brief The MyGraphicsView class
///
class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicsView(View *t_v) : QGraphicsView(), m_view(t_v) { }

protected :
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *t_event) override;
#endif

private:
    View *m_view;
};

///
/// \brief The View class
///
class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString & name, QWidget *parent = 0);

    QGraphicsView *m_view() const;

public slots:
    void zoomIn(int t_scale = 1);
    void zoomOut(int t_scale = 1);

private slots:
    void setupMatrix();

private:
    MyGraphicsView *m_graphicsView;
    QSlider * m_zoomSlider;
};



#endif // MYGRAPHICSVIEW_H
