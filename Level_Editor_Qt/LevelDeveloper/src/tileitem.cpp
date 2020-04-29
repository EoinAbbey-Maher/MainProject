/**
*    tileItem.cpp
*    @author Eoin Abbey-Maher
*    @brief Tile Item to hold the values for if tiles are collidable and positions ||
*           Was created early in development but didn't get used
*/

#include "include/tileitem.h"

TileItem::TileItem()
{

}

TileItem::TileItem(QVector2D t_indexVal, QImage * t_image)
{
    m_indexVal = t_indexVal;
    m_image = t_image;
    this->setData(Qt::DecorationRole, QPixmap::fromImage(*t_image));
}

void TileItem::setTexture(QImage * t_image)
{
    m_image = t_image;
    this->setData(Qt::DecorationRole, QPixmap::fromImage(*m_image));
}

void TileItem::setCollidable(bool t_val)
{
    m_isCollidable = t_val;
}

void TileItem::setIndexVal(QVector2D t_index)
{
    m_indexVal = t_index;
}

QPixmap TileItem::getPixMap()
{
    return this->data(Qt::DecorationRole).value<QPixmap>();
}
