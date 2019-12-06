#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QtWidgets"
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>

#include "mygraphicsview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public signals:



private slots:
    void handleApplyButton();

private: //variables
    QGraphicsScene * scene = new QGraphicsScene(this);
    MyGraphicsView * gView = new MyGraphicsView;
    Ui::MainWindow *ui;

private: //functions
    void setTextures();
    void setupIcons();
    void setupGameGrid();

};
#endif // MAINWINDOW_H
