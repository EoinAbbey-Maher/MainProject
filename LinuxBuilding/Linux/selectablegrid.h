#ifndef SELECTABLEGRID_H
#define SELECTABLEGRID_H

#include <QtWidgets>
#include <QWidget>
#include <QFrame>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE


class SelectableGrid : public QFrame
{
public:
    explicit SelectableGrid(int t_xSize = 20, int t_ySize = 20, QWidget *parent = nullptr);
    QHBoxLayout * layout= new QHBoxLayout;

private:
    void update();

    void checkIfGameSelected();
    void SetSelectedTexture();
    void SetupIconGrid();
    void setupGameGrid(int t_xSize = 20, int t_ySize = 20);

    void mouseClickEvent(QMouseEvent * t_mouseEvent );

    void setupIcons();

    void resizeToContent(QTableView * tableView);
    QTableWidget * m_iconGrid = new QTableWidget(10,2);
    QTableWidget * m_gameGrid = new QTableWidget(20,20);

    QVector<QLabel*> m_Icons;
    QLabel* m_floorIcon = nullptr;
};

#endif // SELECTABLEGRID_H
