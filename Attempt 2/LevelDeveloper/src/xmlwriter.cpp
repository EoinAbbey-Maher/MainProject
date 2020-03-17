#include "include\xmlwriter.h"

XMLWriter::XMLWriter()
{

}

void XMLWriter::WriteTilesToFile(QTableWidget *t_table, QVector<QString> t_TextureNames)
{
    QString fileName = "Map_Data.xml";
 // QString SavePath = QFileDialog::getSaveFileName();

    QString ImageFolder = "Images/";
    QString path = "MapExport/";
    QDir dir;
    QDir imageDir;

    if(!dir.exists(path))
    {
        dir.mkpath(path);
    }

    if(!imageDir.exists(path + ImageFolder))
    {
        dir.mkpath(path + ImageFolder);
    }

     QFile file(path + fileName);
    if(file.open(QIODevice::WriteOnly))
     {

        QXmlStreamWriter xmlWriter(&file);

        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();


        xmlWriter.writeStartElement("Map_Values");
        xmlWriter.writeTextElement("NoOfTextures", QString::number(t_TextureNames.size()));
        xmlWriter.writeTextElement("TotalTiles", QString::number(t_table->rowCount() * t_table->columnCount()));
        xmlWriter.writeTextElement("RowSize", QString::number(t_table->rowCount()));
        xmlWriter.writeTextElement("ColSize", QString::number(t_table->columnCount()));

        for (int i = 0; i < t_TextureNames.size(); i++)
        {
            QImage * image = new QImage(t_TextureNames[i]);

            QString str = t_TextureNames[i];
            str.remove(0,2);


            image->save(path + ImageFolder + str);


            xmlWriter.writeTextElement("Texture" + QString::number(i), t_TextureNames[i]);

        }

        xmlWriter.writeEndElement();
        xmlWriter.writeStartElement("Tiles");


        int tileCount = 0;
        for (int r = 0; r < t_table ->rowCount(); r++)
           {
               for (int c = 0; c < t_table ->columnCount(); c++)
                {
                   QTableWidgetItem* item = t_table->item(r,c);

                    xmlWriter.writeStartElement("Tile" + QString::number(tileCount));
                    xmlWriter.writeTextElement("IndexX", QString::number(c));
                    xmlWriter.writeTextElement("IndexY", QString::number(r));
                    xmlWriter.writeTextElement("PositionX",item->data(Qt::UserRole+1).toString());
                    xmlWriter.writeTextElement("PositionY",item->data(Qt::UserRole+2).toString());
                    xmlWriter.writeTextElement("Image", item->data(Qt::UserRole).toString());
                    xmlWriter.writeTextElement("Type", item->data(Qt::UserRole+3).toString());
                    xmlWriter.writeEndElement();

                    tileCount++;
                }
        }


        xmlWriter.writeEndDocument();
        file.close();

    }

    switch(QMessageBox::question(
           this, tr("Map Export"),
               tr("Map data has been sucessfully exported to Folder"),
                QMessageBox::Ok))
{
    case QMessageBox::Ok:
        qDebug("ok");
        break;

}


}
