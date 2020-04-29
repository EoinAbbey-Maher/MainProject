/**
*    tileItem.h
*    @author Eoin Abbey-Maher
*    @brief Tile Item to hold the values for if tiles are collidable and positions ||
*           Was created early in development but didn't get used
*/

#ifndef TILEITEM_H
#define TILEITEM_H

#include <QObject>
#include <QWidget>
#include <QTableWidgetItem>
#include <QVector2D>
#include <QPixmap>

class XMLWriter;

class TileItem : public QTableWidgetItem
{
public:
    TileItem();
    TileItem(QVector2D t_indexVal , QImage * t_image = nullptr);

    void setTexture(QImage * t_image = nullptr);
    void setCollidable(bool t_val);
    void setIndexVal(QVector2D t_index);

    QPixmap getPixMap();

private:
    QVector2D m_size = QVector2D(20,20);
    QVector2D m_position;
    QVector2D m_indexVal;
    QImage * m_image = nullptr;

    bool m_isEmpty = true;
    bool m_isCollidable = false;
};



#endif // TILEITEM_H
