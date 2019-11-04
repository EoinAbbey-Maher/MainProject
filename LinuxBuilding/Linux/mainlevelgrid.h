#ifndef MAINLEVELGRID_H
#define MAINLEVELGRID_H

#include <QFrame>

namespace Ui {
class MainLevelGrid;
}

class MainLevelGrid : public QFrame
{
    Q_OBJECT

public:
    explicit MainLevelGrid(QWidget *parent = nullptr);
    ~MainLevelGrid();

private:
    Ui::MainLevelGrid *ui;
};

#endif // MAINLEVELGRID_H
