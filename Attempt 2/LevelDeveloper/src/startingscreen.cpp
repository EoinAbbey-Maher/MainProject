#include "include\startingscreen.h"
#include "ui_startingscreen.h"

StartingScreen::StartingScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartingScreen)
{
    this->setWindowTitle("Jigsaw Tiled Map Designer");

    ui->setupUi(this);


    connect(ui->m_NewLevelBut, SIGNAL(released()), this, SLOT(HandleNewButton()));
    connect(ui->m_LoadLevelButton, SIGNAL(released()), this, SLOT(HandleLoadButton()));
    connect(ui->m_quitButton, SIGNAL(released()), this, SLOT(HandleCloseButton()));
}

StartingScreen::~StartingScreen()
{
    delete ui;
}

void StartingScreen::HandleNewButton()
{
    close();
    m_LayoutScreen = new MapLayoutScreen();
    m_LayoutScreen->show();
}


void StartingScreen::HandleCloseButton()
{
    close();
}

void StartingScreen::HandleLoadButton()
{

}

