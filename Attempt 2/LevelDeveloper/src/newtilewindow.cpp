#include "include\newtilewindow.h"
#include "ui_newtilewindow.h"

NewTileWindow::NewTileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewTileWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Jigsaw Tiled Map Designer");
}

NewTileWindow::~NewTileWindow()
{
    delete ui;
}
