#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupIcons();

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupIcons()
{
    for (int r = 0; r < ui->Icon_Table->rowCount(); r++)
       {
           for (int c = 0; c < ui->Icon_Table->columnCount(); c++)
           {
               QTableWidgetItem * item = new QTableWidgetItem;
               item->setIcon(QIcon(":/Images/floor.jpg"));
               ui->Icon_Table->setItem(r,c,item);
           }
    }
}


