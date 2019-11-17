#include "selectablegrid.h"

//------------------------------------------------------------------------------
// Grid Constructor
// -----------------------------------------------------------------------------
SelectableGrid::SelectableGrid(int t_xSize, int t_ySize, QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setMinimumSize(0,0);

    SetupIconGrid();
    setupGameGrid(t_xSize, t_ySize);

    layout->addWidget( m_iconGrid);
    layout->addWidget(m_gameGrid);

   // layout->setSizeConstraint(QLayout::SetFixedSize);
     //m_iconGrid->show();

    connect(m_iconGrid, SIGNAL(Mouse_Pressed()), this, SLOT(SetSelectedTexture()));
    connect(m_gameGrid, SIGNAL(Mouse_Pressed()), this, SLOT(SetSelectedTexture()));
}

// --------------------------------------------------------------------------------------
// Sets grid window Size
//---------------------------------------------------------------------------------------
void SelectableGrid::resizeToContent(QTableWidget * table)
{
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    QRect rect = table->geometry();
    int tableWidth = 2 + table->verticalHeader()->width();
    for (int i = 0;i < table->columnCount();i++)
    {
            tableWidth += table->columnWidth(i);
    }
    rect.setWidth(tableWidth);

    int tableHeight = 2 + table->horizontalHeader()->height();
    for (int i = 0; i < table->rowCount();i++)
    {
        tableWidth += table->columnWidth(i);
    }
    rect.setHeight(tableHeight);

    table->setGeometry(rect);
}


// -------------------------------------------------------------------------------------
//               Setup Selectable Icons to Vector
// -------------------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
//                  Checking for mouse Click
// -----------------------------------------------------------------------------
void SelectableGrid::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
      emit Mouse_Pressed();
      qDebug() << "Left Button";
    }
}

void SelectableGrid::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
      emit Mouse_Pressed();
      qDebug() << "Double Left Button";
    }
}

void SelectableGrid::Mouse_Pressed()
{
    SetSelectedTexture();
     qDebug() << "Left Button";
}

// ----------------------------------------------------------------------------
//                             Set new Textures
// ----------------------------------------------------------------------------
void SelectableGrid::SetSelectedTexture()
{
    if(m_gameGrid->selectedItems().count() > 0)
    {
        for (int i = 0; i <m_gameGrid->selectedItems().count(); i++) {

            QPixmap image = m_iconGrid->selectedItems().at(i)->data(Qt::DecorationRole).value<QPixmap>();

            m_gameGrid->selectedItems().at(i)->setData(Qt::DecorationRole, image);
        }
    }
}

// ------------------------------------------------------------------------------------
// Setup Selectable Textures
// ------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
//                      Setup the Initial Game Grid
// ---------------------------------------------------------------------------
void SelectableGrid::setupGameGrid(int t_xSize, int t_ySize)
{
    m_gameGrid->verticalHeader()->setDefaultSectionSize(100);
    m_gameGrid->horizontalHeader()->setDefaultSectionSize(100);

    m_gameGrid->setColumnCount(t_xSize);
    m_gameGrid->setRowCount(t_ySize);

    m_gameGrid ->verticalHeader()->hide();
    m_gameGrid ->horizontalHeader()->hide();

    int colCt = 0;
    int rowCt = 0;
    for (int i = 0 ; i && i < m_gameGrid->rowCount(); i++) {
        m_Icons.push_back(new QLabel(this));
        QLabel * label = new QLabel;
        label->setPixmap(QPixmap(":/Images/empty.jpg"));

        m_gameGrid->setCellWidget(rowCt, colCt, label);
        colCt++;

        if(colCt >= m_gameGrid->columnCount())
        {
            colCt  = 0;
            rowCt++;
        }
    }

    m_gameGrid ->setAttribute(Qt::WA_DeleteOnClose);
    resizeToContent(m_gameGrid);
}
