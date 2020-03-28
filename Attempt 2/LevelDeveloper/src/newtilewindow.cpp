#include "include\newtilewindow.h"
#include "ui_newtilewindow.h"

NewTileWindow::NewTileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewTileWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Jigsaw Tiled Map Designer");


}

NewTileWindow::NewTileWindow(QVector<QString> &t_textures, QTableWidget &t_table, QWidget *parent):
    m_table(&t_table),
    m_textures(&t_textures),
    ui(new Ui::NewTileWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Jigsaw Tiled Map Designer | Add New Tile");

    connect(ui->m_SelectFileButton, SIGNAL(released()), this, SLOT(handleLocationButton()));
    connect(ui->m_CancelButton, SIGNAL(released()), this, SLOT(handleCancelButton()));
    connect(ui->m_AddButton, SIGNAL(released()), this, SLOT(handleConfirmButton()));

}



NewTileWindow::~NewTileWindow()
{
    delete ui;
}

void NewTileWindow::handleConfirmButton()
{
    QImageReader reader(m_tempLocation);
    reader.setAutoTransform(true);

    QImage newImage = reader.read();

    m_textures->push_back(m_tempLocation);

    QTableWidgetItem * widgetItem;
    bool inserted = false;
    for (int r = 0; r < m_table->rowCount(); r++)
    {
        for (int c = 0; c < m_table->columnCount(); c++)
        {
            widgetItem = m_table->item(r,c);
            if(widgetItem == nullptr)
            {
                TileItem * tile = new TileItem;
                tile->setTexture(&newImage);
                tile->setData(Qt::UserRole, m_tempLocation);
                tile->setData(Qt::UserRole +3, "Floor");
                tile->setData(Qt::DecorationRole, QPixmap::fromImage(newImage.scaled(50,50)));
                tile->setIndexVal(QVector2D(r,c));
                m_table->setItem(r,c,tile);
                inserted = true;
                break;
            }
            if(inserted)
            {
                break;
            }

        }
        if(!inserted && r == m_table->rowCount())
        {
            m_table->insertRow(m_table->rowCount());
        }
    }


}

void NewTileWindow::handleCancelButton()
{

}

void NewTileWindow::handleLocationButton()
{



}
