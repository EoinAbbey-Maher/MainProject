#include "gamegrid.h"

GameGrid::GameGrid(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400,800);

    m_grid->columnWidth(50);
    m_grid->rowHeight(5);

    m_grid->verticalHeader()->hide();
    m_grid->horizontalHeader()->hide();

    m_grid->show();
    m_grid->setAttribute(Qt::WA_DeleteOnClose);


}

GameGrid::GameGrid(int t_xSize, int t_ySize, QWidget *parent) : QWidget(parent)
{
    setMinimumSize(400,800);

    m_grid->columnWidth(50);
    m_grid->rowHeight(5);

    m_grid->horizontalHeader()->hide();
    m_grid->verticalHeader()->hide();
    m_grid->setColumnCount(t_xSize);
    m_grid->setRowCount(t_ySize);



    m_grid->show();
    m_grid->setAttribute(Qt::WA_DeleteOnClose);

}
