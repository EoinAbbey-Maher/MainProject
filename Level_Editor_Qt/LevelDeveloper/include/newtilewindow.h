/**
*    newtilewindow.h
*    @author Eoin Abbey-Maher
*    @brief Setup and Variables of the new tile window where New custom user tiles are added
*/

#ifndef NEWTILEWINDOW_H
#define NEWTILEWINDOW_H

#include <QMainWindow>

#include "QtWidgets"
#include <QWidget>
#include <QTableWidget>
#include <QString>
#include <QImage>
#include <QVector>
#include <QDir>

#include "tileitem.h"

namespace Ui {
class NewTileWindow;
}

class NewTileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewTileWindow(QWidget *parent = nullptr);
    NewTileWindow(QVector<QPair<QString, QString>> & t_textures , QTableWidget& t_table, QWidget *parent = nullptr);
    ~NewTileWindow();

private slots:
    void handleConfirmButton();
    void handleCancelButton();
    void handleLocationButton();

private: //variables
    Ui::NewTileWindow *m_ui;
    QVector<QPair<QString, QString>>* m_textures;
    QTableWidget* m_table;

    QString m_tempLocation;

private: // Functions

    void selectPath();
    void retrieveName();
};

#endif // NEWTILEWINDOW_H
