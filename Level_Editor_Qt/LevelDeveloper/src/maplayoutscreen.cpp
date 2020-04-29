/**
*    maplayoutscreen.cpp
*    @brief Setup and Variables of the Map Setup Screen
*    @author Eoin Abbey-Maher
*/

#include "include/maplayoutscreen.h"
#include "ui_maplayoutscreen.h"

MapLayoutScreen::MapLayoutScreen(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MapLayoutScreen)
{
    m_ui->setupUi(this);

    this->setWindowTitle("Jigsaw Tiled Map Designer");

    connect(m_ui->m_createButton, SIGNAL(released()), this, SLOT(handleNewButton()));
    connect(m_ui->m_cancelButton, SIGNAL(released()), this, SLOT(cancelButton()));
}


MapLayoutScreen::~MapLayoutScreen()
{
    delete m_ui;
}

void MapLayoutScreen::handleNewButton()
{
    close();
    m_mainWindow = new MainWindow(m_ui->m_HeightValue->value(), m_ui->m_WidthValue->value());
    m_mainWindow->show();

}

void MapLayoutScreen::cancelButton()
{
    close();
    m_startScreen = new StartingScreen();
    m_startScreen->show();
}
