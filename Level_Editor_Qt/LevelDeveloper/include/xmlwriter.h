/**
*    xmlwriter.h
*    @author Eoin Abbey-Maher
*    @brief XML Writer and Reader for exporting and loading in levels
*/


#ifndef XMLWRITER_H
#define XMLWRITER_H


#include <QObject>
#include <QtWidgets>
#include <qtablewidget.h>
#include <qfiledialog.h>
#include <QMessageBox>
#include <QFile>
#include <QtXml>

#include <iostream>
#include "tileitem.h"

class TileItem;

class XMLWriter : public QWidget
{
    Q_OBJECT
public:
    XMLWriter();

    void WriteTilesToFile(QTableWidget * t_mapTable,QTableWidget * t_nodeTable, QVector<QPair<QString,QString>> t_TextureNames);

    void ReadExistingFile();
signals:


private:
    QString m_XML_Name = "Map_Data.xml";

public slots:
};

#endif // XMLWRITER_H
