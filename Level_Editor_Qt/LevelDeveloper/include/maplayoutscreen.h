/**
*    maplayoutscreen.h
*    @brief Setup and Variables of the Map Setup Screen
*    @author Eoin Abbey-Maher
*/

#ifndef MAPLAYOUTSCREEN_H
#define MAPLAYOUTSCREEN_H

#include <QMainWindow>
#include "mainwindow.h"
#include "startingscreen.h"

class StartingScreen;
class XMLWriter;
class MainWindow;


namespace Ui {
class MapLayoutScreen;
}

class MapLayoutScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapLayoutScreen(QWidget *parent = nullptr);
    ~MapLayoutScreen();

signals:

public slots:
    void handleNewButton();
    void cancelButton();

private: //Variables
    Ui::MapLayoutScreen * m_ui;
    MainWindow * m_mainWindow;
    StartingScreen * m_startScreen;
};


#endif // MAPLAYOUTSCREEN_H
