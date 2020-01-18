#include "xmlwriter.h"

XMLWriter::XMLWriter()
{

}

void XMLWriter::WriteTilesToFile(QTableWidget *t_table, QVector<QString> t_TextureNames)
{
    QString fileName = "Map_Data.xml";
    QString path = "MapExport/";
    QDir dir;

    if(!dir.exists(path))
    {
        dir.mkpath(path);
    }

    QFile file(path + fileName);
    if(file.open(QIODevice::WriteOnly))
     {

        QXmlStreamWriter xmlWriter(&file);

        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();


        xmlWriter.writeStartElement("Map Values");
        xmlWriter.writeTextElement("NoOfTextures", QString::number(t_TextureNames.size()));
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
                    xmlWriter.writeTextElement("Position",item->data(Qt::UserRole+1).toString());
                    xmlWriter.writeTextElement("Image", item->data(Qt::UserRole).toString());
                    xmlWriter.writeEndElement();

                    tileCount++;
                }
        }


        xmlWriter.writeEndDocument();
        file.close();

    }

    switch(QMessageBox::question(
           this, tr("Map Export"),
               tr("Map data has been sucessfully exported to the root folder of this application."),
                QMessageBox::Ok))
{
    case QMessageBox::Ok:
        qDebug("ok");
        break;

}

    //QDir imagePaths("Images/floor.png");
    //if(QFile::exists("Images/floor.png"))
    //{
      //  qDebug() << "Image Exists";
  //      QFile::copy("Images/floor.png","MapExport/floor.png");
    //}
   // else
    //{
      //  qDebug() << "no image in location";
    //}



}
