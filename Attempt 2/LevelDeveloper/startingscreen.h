#ifndef STARTINGSCREEN_H
#define STARTINGSCREEN_H

#include <QMainWindow>

#include <QtWidgets>
#include <QWidget>


#include "mainwindow.h"

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
    void HandleNewButton();
    void HandleCloseButton();
    void HandleLoadButton();


private:
    MainWindow *m_levelWindow;

private:
    Ui::StartingScreen *ui;
};

#endif // STARTINGSCREEN_H
