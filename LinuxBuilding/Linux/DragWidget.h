#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QFrame>
#include <QVector>
#include <QtWidgets>


QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE


class DragWidget : public QFrame
{
public:
    explicit DragWidget(QWidget *parent = nullptr);


protected:
    QVector<QLabel*> m_Icons;
    QLabel* m_floorIcon = nullptr;

    void SetupImages();
    void dragEnterEvent(QDragEnterEvent * event) override;
    void dragMoveEvent(QDragMoveEvent * event) override;
    void dropEvent(QDropEvent * event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // DRAGWIDGET_H
