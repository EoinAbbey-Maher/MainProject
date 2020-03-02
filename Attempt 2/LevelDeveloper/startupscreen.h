#ifndef STARTUPSCREEN_H
#define STARTUPSCREEN_H

#include <QtWidgets>
#include <QWidget>

#include <QDialog>

#include "mainwindow.h"

namespace Ui {
class StartupScreen;
}

class StartupScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartupScreen(QWidget *parent = nullptr);
    ~StartupScreen();


signals:


private slots:
    void HandleNewButton();
    void HandleCloseButton();
    void HandleLoadButton();

    void keyPressEvent(QKeyEvent * t_event);

private:
    Ui::StartupScreen *ui;
};

#endif // STARTUPSCREEN_H
