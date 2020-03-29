#ifndef XMLWRITER_H
#define XMLWRITER_H


#include <QObject>
#include <QtWidgets>
#include <qtablewidget.h>
#include <qfiledialog.h>
#include <QMessageBox>

#include "tileitem.h"

class XMLWriter : public QWidget
{
    Q_OBJECT
public:
    XMLWriter();

    void WriteTilesToFile(QTableWidget * t_table, QVector<QPair<QString,QString>> t_TextureNames);
signals:

public slots:
};

#endif // XMLWRITER_H
