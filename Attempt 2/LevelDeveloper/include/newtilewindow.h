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
    NewTileWindow(QVector<QString> & t_textures , QTableWidget& t_table, QWidget *parent = nullptr);
    ~NewTileWindow();

private slots:
    void handleConfirmButton();
    void handleCancelButton();
    void handleLocationButton();

private:
    Ui::NewTileWindow *ui;
    QVector<QString>* m_textures;
    QTableWidget* m_table;

    QString m_tempLocation;


    void selectPath();
    void retrieveName();
};

#endif // NEWTILEWINDOW_H
