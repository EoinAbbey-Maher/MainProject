#include "startupscreen.h"
#include "ui_startupscreen.h"

StartupScreen::StartupScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupScreen)
{
    ui->setupUi(this);

    connect(ui->m_NewLevelBut, SIGNAL(released()), this, SLOT(HandleNewButton()));
    connect(ui->m_LoadLevelButton, SIGNAL(released()), this, SLOT(HandleLoadButton()));
    connect(ui->m_quitButton, SIGNAL(released()), this, SLOT(HandleCloseButton()));


}

StartupScreen::~StartupScreen()
{
    delete ui;
}

void StartupScreen::HandleNewButton()
{
    MainWindow m;
}

void StartupScreen::HandleCloseButton()
{

}

void StartupScreen::HandleLoadButton()
{

}

