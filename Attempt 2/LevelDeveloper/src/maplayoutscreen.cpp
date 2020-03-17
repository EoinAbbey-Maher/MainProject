#include "include\maplayoutscreen.h"
#include "ui_maplayoutscreen.h"

MapLayoutScreen::MapLayoutScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MapLayoutScreen)
{
    ui->setupUi(this);

    this->setWindowTitle("Jigsaw Tiled Map Designer");

    connect(ui->m_createButton, SIGNAL(released()), this, SLOT(handleNewButton()));
    connect(ui->m_cancelButton, SIGNAL(released()), this, SLOT(cancelButton()));
}


MapLayoutScreen::~MapLayoutScreen()
{
    delete ui;
}

void MapLayoutScreen::handleNewButton()
{
    close();
    m_mainWindow = new MainWindow(ui->m_HeightValue->value(), ui->m_widthValue->value());
    m_mainWindow->show();

}

void MapLayoutScreen::cancelButton()
{
    close();
    m_startScreen = new StartingScreen();
    m_startScreen->show();
}
