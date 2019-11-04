#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QTableWidget>
#include <QtWidgets>
#include <QFrame>
#include <QWidget>

class GameGrid : public QWidget
{
    //Q_OBJECT
public:
    explicit GameGrid(QWidget *parent = nullptr);
    explicit GameGrid(int t_xSize, int t_ySize, QWidget *parent = nullptr);
protected:
    QTableWidget * m_grid = new QTableWidget(5,5);
signals:

public slots:
};

#endif // GAMEGRID_H
