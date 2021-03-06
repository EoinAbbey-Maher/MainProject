/**
*    newtilewindow.cpp
*    @author Eoin Abbey-Maher
*    @brief Setup and Variables of the new tile window where New Custom uaer tiles are added
*/

#include "include/newtilewindow.h"
#include "ui_newtilewindow.h"

NewTileWindow::NewTileWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::NewTileWindow)
{
    m_ui->setupUi(this);
    this->setWindowTitle("Jigsaw Tiled Map Designer");


}

NewTileWindow::NewTileWindow(QVector<QPair<QString, QString>> &t_textures, QTableWidget &t_table, QWidget *parent):
    QMainWindow(parent),
    m_ui(new Ui::NewTileWindow),
    m_table(&t_table),
    m_textures(&t_textures)

{
    m_ui->setupUi(this);
    this->setWindowTitle("Jigsaw Tiled Map Designer | Add New Tile");

    setWindowFlag(Qt::Popup);

    connect(m_ui->m_SelectFileButton, SIGNAL(released()), this, SLOT(handleLocationButton()));
    connect(m_ui->m_CancelButton, SIGNAL(released()), this, SLOT(handleCancelButton()));
    connect(m_ui->m_AddButton, SIGNAL(released()), this, SLOT(handleConfirmButton()));

}



NewTileWindow::~NewTileWindow()
{
    delete m_ui;
}

void NewTileWindow::handleConfirmButton()
{
    QImageReader reader(m_tempLocation);
    reader.setAutoTransform(true);

    QImage newImage = reader.read();

    m_textures->push_back(QPair<QString, QString>(m_tempLocation,m_ui->m_TileNameInput->toPlainText().simplified()));

    QTableWidgetItem * widgetItem;
    bool inserted = false;
    for (int r = 0; r < m_table->rowCount(); r++)
    {
        for (int c = 0; c < m_table->columnCount(); c++)
        {
            if(!inserted)
            {
                widgetItem = m_table->item(r,c);
            if(widgetItem == nullptr)
            {
                TileItem * tile = new TileItem;
                tile->setTexture(&newImage);
                tile->setData(Qt::UserRole, m_ui->m_TileNameInput->toPlainText().simplified());
                tile->setData(Qt::UserRole +3, m_ui->m_TypeSelection->currentText());
                tile->setData(Qt::DecorationRole, QPixmap::fromImage(newImage.scaled(50,50)));
                tile->setToolTip("Name: " + m_ui->m_TileNameInput->toPlainText().simplified() + "\nType: " + m_ui->m_TileTypeText->text());
                tile->setIndexVal(QVector2D(r,c));
                m_table->setItem(r,c,tile);
                inserted = true;
                break;
            }

            }
            else
            {
                break;
            }
        }
        if(!inserted && r == m_table->rowCount())
        {
            m_table->insertRow(m_table->rowCount());
            m_table->resize((m_table->rowCount()+1) * 50, (m_table->columnCount()+1) * 50);
        }
    }

    close();

}

void NewTileWindow::handleCancelButton()
{
    close();
}

void NewTileWindow::handleLocationButton()
{
    qDebug() << "Location Button Pressed";
    m_tempLocation = QFileDialog::getOpenFileName(this, tr("Open Image"));
    m_ui->m_FileLocationText->setText(m_tempLocation);
    show();
}

