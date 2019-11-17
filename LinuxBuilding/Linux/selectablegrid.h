#ifndef SELECTABLEGRID_H
#define SELECTABLEGRID_H

#include <QtWidgets>
#include <QWidget>
#include <QFrame>
#include <QTableWidget>
#include <QEvent>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE


class SelectableGrid : public QFrame
{
public:
    explicit SelectableGrid(int t_xSize = 20, int t_ySize = 20, QWidget *parent = nullptr);
    QHBoxLayout * layout= new QHBoxLayout;

signals:
    void Mouse_Pressed();
    void Mouse_Left();

private slots:
    void SetSelectedTexture();

private:
    void update();

    void checkIfGameSelected();

    void SetupIconGrid();
    void setupGameGrid(int t_xSize = 20, int t_ySize = 20);

    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);


    void setupIcons();

    void resizeToContent(QTableWidget * tableView);
    QTableWidget * m_iconGrid = new QTableWidget(10,2);
    QTableWidget * m_gameGrid = new QTableWidget(20,20);

    QVector<QLabel*> m_Icons;
    QLabel* m_floorIcon = nullptr;
};

#endif // SELECTABLEGRID_H
