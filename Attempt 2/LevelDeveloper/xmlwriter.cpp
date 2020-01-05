#include "xmlwriter.h"

XMLWriter::XMLWriter()
{

}

void XMLWriter::WriteTilesToFile(QTableWidget *t_table)
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

        xmlWriter.writeStartElement("Tiles");

        xmlWriter.writeStartElement("Tile1");
        xmlWriter.writeStartElement("Position", "PositionValue");
        xmlWriter.writeStartElement("Image", "ImagePath");

        xmlWriter.writeEndElement();
        file.close();

    }

//    QDir imagePaths("Images/floor.png");
  //  if(QFile::exists("Images/floor.png"))
    //{
      //  qDebug() << "Image Exists";
  //      QFile::copy("Images/floor.png","MapExport/floor.png");
    //}
   // else
    //{
      //  qDebug() << "no image in location";
    //}



}
