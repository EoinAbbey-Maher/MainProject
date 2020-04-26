#ifndef NEWTILEWINDOW_H
#define NEWTILEWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewTileWindow;
}

class NewTileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewTileWindow(QWidget *parent = nullptr);
    ~NewTileWindow();

private:
    Ui::NewTileWindow *ui;
};

#endif // NEWTILEWINDOW_H
