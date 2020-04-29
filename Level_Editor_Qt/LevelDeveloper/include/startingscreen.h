/**
*    startingscreen.h
*    @author Eoin Abbey-Maher
*    @brief Introduction Screen when the program is first launched, allows for User to select to make a new level or load an existing one
*/

#ifndef STARTINGSCREEN_H
#define STARTINGSCREEN_H

#include <QMainWindow>

#include <QtWidgets>
#include <QWidget>


#include "mainwindow.h"
#include "maplayoutscreen.h"


class MapLayoutScreen;
class XMLWriter;

namespace Ui {
class StartingScreen;
}

class StartingScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartingScreen(QWidget *parent = 0);
    ~StartingScreen();


signals:


public slots:
    void handleNewButton();
    void handleCloseButton();
    void handleLoadButton();


private: //variables
    MapLayoutScreen * m_LayoutScreen;
    Ui::StartingScreen *m_ui;
};

#endif // STARTINGSCREEN_H
