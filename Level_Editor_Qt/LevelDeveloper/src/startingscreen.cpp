/**
*    startingscreen.cpp
*    @author Eoin Abbey-Maher
*    @brief Introduction Screen when the program is first launched, allows for User to select to make a new level or load an existing one
*/


#include "include/startingscreen.h"
#include "include/xmlwriter.h"
#include "ui_startingscreen.h"


StartingScreen::StartingScreen(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::StartingScreen)
{
    this->setWindowTitle("Jigsaw Tiled Map Designer");

    m_ui->setupUi(this);


    connect(m_ui->m_NewLevelBut, SIGNAL(released()), this, SLOT(handleNewButton()));
    connect(m_ui->m_LoadLevelButton, SIGNAL(released()), this, SLOT(handleLoadButton()));
    connect(m_ui->m_quitButton, SIGNAL(released()), this, SLOT(handleCloseButton()));
}

StartingScreen::~StartingScreen()
{
    delete m_ui;
}

void StartingScreen::handleNewButton()
{
    close();
    m_LayoutScreen = new MapLayoutScreen();
    m_LayoutScreen->show();
}


void StartingScreen::handleCloseButton()
{
    close();
}

void StartingScreen::handleLoadButton()
{
    XMLWriter xml;

    xml.ReadExistingFile();
}

