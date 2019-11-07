#include "selectablegrid.h"


SelectableGrid::SelectableGrid(int t_xSize, int t_ySize, QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setMinimumSize(100,500);

    SetupIconGrid();
    setupGameGrid(t_xSize, t_ySize);

    layout->addWidget( m_iconGrid);
    layout->addWidget(m_gameGrid);

   // layout->setSizeConstraint(QLayout::SetFixedSize);
     //m_iconGrid->show();
}

void SelectableGrid::checkIfGameSelected()
{

}

void SelectableGrid::resizeToContent(QTableView * tableView)
{
    int count = tableView->verticalHeader()->count();
    int scrollBarheight = tableView->horizontalScrollBar()->height();
    int horizontalHeaderHeight = tableView->horizontalHeader()->height();
    int rowTotalHeight = 0;

    for(int i = 0; i < count; ++i)
    {
        rowTotalHeight +=tableView->verticalHeader()->sectionSize(i);

    }
    tableView->setMinimumHeight(horizontalHeaderHeight+rowTotalHeight + scrollBarheight);


    count = tableView->horizontalHeader()->count();
    int scrollBarWidth = tableView->verticalScrollBar()->width();
    int horizontalHeaderWidth = tableView->horizontalHeader()->width();
    int rowTotalWidth= 0;

    for(int i = 0; i < count; ++i)
    {
        rowTotalWidth +=tableView->verticalHeader()->sectionSize(i);

    }
    tableView->setMinimumWidth(horizontalHeaderWidth+rowTotalHeight + scrollBarWidth);

}

void SelectableGrid::setupIcons()
{
    int rowCt = 0;
    int colCt = 0;

    for (int i = 0 ; i  < 4 && i < m_iconGrid->rowCount(); i++) {
        m_Icons.push_back(new QLabel(this));
        m_Icons[i]->setPixmap(QPixmap(":/Images/floor.jpg"));


        m_iconGrid->setCellWidget(rowCt, colCt, m_Icons[i]);
        colCt++;

        if(colCt >= m_iconGrid->columnCount())
        {
            colCt  = 0;
            rowCt++;
        }
    }


  //   m_iconGrid->setCellWidget(1, 0, m_Icons[1]);

    for (int i = 0 ; i  < m_Icons.size(); i++) {

        m_Icons[i]->show();
        m_Icons[i]->setAttribute(Qt::WA_DeleteOnClose);

    }
}

void SelectableGrid::SetupIconGrid()
{
    m_iconGrid->setSelectionMode(QAbstractItemView::SingleSelection);
    m_iconGrid->verticalHeader()->setDefaultSectionSize(100);
    m_iconGrid->horizontalHeader()->setDefaultSectionSize(100);

    m_iconGrid ->verticalHeader()->hide();
    m_iconGrid ->horizontalHeader()->hide();

    m_iconGrid->setAttribute(Qt::WA_DeleteOnClose);
    setupIcons();
    resizeToContent(m_iconGrid);
}

void SelectableGrid::setupGameGrid(int t_xSize, int t_ySize)
{
    m_gameGrid->verticalHeader()->setDefaultSectionSize(100);
    m_gameGrid->horizontalHeader()->setDefaultSectionSize(100);

    m_gameGrid->setColumnCount(t_xSize);
    m_gameGrid->setRowCount(t_ySize);

    m_gameGrid ->verticalHeader()->hide();
    m_gameGrid ->horizontalHeader()->hide();

    m_gameGrid ->setAttribute(Qt::WA_DeleteOnClose);
    resizeToContent(m_gameGrid);
}
