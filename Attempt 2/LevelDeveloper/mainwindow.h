#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QImage>

#include "mygraphicsview.h"
#include "tile.h"


QT_BEGIN_NAMESPACE
class QSplitter;
class QGraphicsScene;

QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {}
private:
    void setupMatrix();
    void initScene();

    QGraphicsScene * m_scene;
};
#endif // MAINWINDOW_H
