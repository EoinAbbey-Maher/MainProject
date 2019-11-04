#ifndef SELECTABLEGRID_H
#define SELECTABLEGRID_H

#include <QtWidgets>
#include <QWidget>
#include <QFrame>
#include <QTableWidget>

class SelectableGrid : public QFrame
{
public:
    explicit SelectableGrid(QWidget *parent = nullptr);
    explicit SelectableGrid(int t_xSize, int t_ySize, QWidget *parent = nullptr);

protected:
    QTableWidget * m_grid = new QTableWidget(5,5);
};

#endif // SELECTABLEGRID_H
