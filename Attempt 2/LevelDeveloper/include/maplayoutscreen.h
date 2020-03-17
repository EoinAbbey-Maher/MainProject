#ifndef MAPLAYOUTSCREEN_H
#define MAPLAYOUTSCREEN_H

#include <QMainWindow>
#include "mainwindow.h"
#include "startingscreen.h"

class StartingScreen;
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

private:
    Ui::MapLayoutScreen *ui;
    MainWindow * m_mainWindow;
    StartingScreen * m_startScreen;

};


#endif // MAPLAYOUTSCREEN_H
