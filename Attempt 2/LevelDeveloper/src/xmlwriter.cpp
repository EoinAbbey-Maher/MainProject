#include "include/xmlwriter.h"

XMLWriter::XMLWriter()
{

}

void XMLWriter::WriteTilesToFile(QTableWidget *t_table, QVector<QPair<QString,QString>> t_TextureNames)
{
    QString fileName = m_XML_Name;
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
            QImage * image = new QImage(t_TextureNames[i].first);

            QString str = t_TextureNames[i].second + ".png";

            image->save(path + ImageFolder + str);


            xmlWriter.writeTextElement("Texture" + QString::number(i), t_TextureNames[i].second);

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

void XMLWriter::ReadExistingFile(QTableWidget *t_table, QVector<QPair<QString, QString>>& t_TextureNames)
{
    QString folderPath = QFileDialog::getExistingDirectory(this,tr("Image Folder"));
    QString fileName = m_XML_Name;

    if(folderPath.isEmpty())
    {
        switch(QMessageBox::question(
                   this, tr("Map Import"), tr("Folder Is Empty"), QMessageBox::Ok))
        {
            case QMessageBox::Ok:
                qDebug("ok");
                break;

        }

        return;
    }

    QDomDocument xmlDoc;

    QFile file(folderPath + "/" + fileName);

    if(!file.open(QIODevice::ReadOnly))
    {
        switch(QMessageBox::question(
                   this, tr("Map Import"), tr("cannot Open XML File"), QMessageBox::Ok))
        {
            case QMessageBox::Ok:
                qDebug("ok");
                break;

        }

        return;
    }

    xmlDoc.setContent(&file);
    file.close();
    QDomElement mapValues = xmlDoc.firstChildElement("MapValues");
    QDomText noOfTexturesXML = mapValues.firstChildElement("NoOfTextures").firstChild().toText();
    QDomText TotalTilesXML = mapValues.firstChildElement("TotalTiles").firstChild().toText();
    QDomText mapheightXML= mapValues.firstChildElement("RowSize").firstChild().toText();
    QDomText mapWidthXML = mapValues.firstChildElement("ColSize").firstChild().toText();

    int noOFTexturesInt = noOfTexturesXML.data().toInt();
    int TotalTilesInt = TotalTilesXML.data().toInt();
    int mapHeightInt = mapheightXML.data().toInt();
    int mapWidthInt = mapWidthXML.data().toInt();

    QVector<QPair<QString, QImage*>> name_ImagePair;

    for(int i = 0; i < noOFTexturesInt; i++)
    {
        QString str = "Texture" + QString::number(i);
        char textureArr[11] = {};
        strcpy(textureArr, str.toStdString().c_str());

        QDomText ImageLink = mapValues.firstChildElement(textureArr).firstChild().toText();

        t_TextureNames.clear();

        t_TextureNames.push_back(QPair<QString, QString>(("Images/" + ImageLink.data() + ".png"),ImageLink.data()));

        QImage * image = new QImage(t_TextureNames[i].first);

        name_ImagePair.push_back(QPair<QString, QImage*>((t_TextureNames[i].second),(image)));
    }


    int  t = 0;

    for (int r = 0; r < mapHeightInt; r++) {
        for (int c = 0; c < mapWidthInt; c++) {

        /// Create New Game Grid
        /// Create Tile Object
        /// Assign All Values TO New Map Tile
        ///

        }
    }

//        int t = 0;

//        for (int i = 0; i < mapHeightInt; i++)
//        {
//            for (int j = 0; j < mapWidthInt; j++)
//            {

//                std::string str = "Tile" + std::to_string(t);
//                char tilearr[10] = {};

//                strcpy_s(tilearr, str.c_str());


//                XMLText* indexX = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexX")->FirstChild()->ToText();
//                XMLText* indexY = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexY")->FirstChild()->ToText();
//                XMLText* PositionX = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionX")->FirstChild()->ToText();
//                XMLText* PositionY = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionY")->FirstChild()->ToText();
//                XMLText* TypeXML = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionY")->FirstChild()->ToText();

//                XMLText* ImageURL = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("Image")->FirstChild()->ToText();

//                std::string imgStr = ImageURL->Value();

//                m_tiles[i][j].indexPosition = sf::Vector2i(std::stoi(indexX->Value()), std::stoi(indexY->Value()));
//                m_tiles[i][j].m_position = sf::Vector2f(std::stof(PositionX->Value()), std::stof(PositionY->Value()));
//                m_tiles[i][j].m_ImgAddress = imgStr;

//                m_tiles[i][j].init(m_textureDict);

//                t++;
//            } // !for j

//        } // !for i

//        std::cout << "builder" << std::endl;




//        xmlWriter.setAutoFormatting(true);
//        xmlWriter.writeStartDocument();


//        xmlWriter.writeStartElement("Map_Values");
//        xmlWriter.writeTextElement("NoOfTextures", QString::number(t_TextureNames.size()));
//        xmlWriter.writeTextElement("TotalTiles", QString::number(t_table->rowCount() * t_table->columnCount()));
//        xmlWriter.writeTextElement("RowSize", QString::number(t_table->rowCount()));
//        xmlWriter.writeTextElement("ColSize", QString::number(t_table->columnCount()));

//        for (int i = 0; i < t_TextureNames.size(); i++)
//        {
//            QImage * image = new QImage(t_TextureNames[i].first);

//            QString str = t_TextureNames[i].second + ".png";

//            image->save(path + ImageFolder + str);


//            xmlWriter.writeTextElement("Texture" + QString::number(i), t_TextureNames[i].second);

//        }

//        xmlWriter.writeEndElement();
//        xmlWriter.writeStartElement("Tiles");


//        int tileCount = 0;
//        for (int r = 0; r < t_table ->rowCount(); r++)
//           {
//               for (int c = 0; c < t_table ->columnCount(); c++)
//                {
//                   QTableWidgetItem* item = t_table->item(r,c);

//                    xmlWriter.writeStartElement("Tile" + QString::number(tileCount));
//                    xmlWriter.writeTextElement("IndexX", QString::number(c));
//                    xmlWriter.writeTextElement("IndexY", QString::number(r));
//                    xmlWriter.writeTextElement("PositionX",item->data(Qt::UserRole+1).toString());
//                    xmlWriter.writeTextElement("PositionY",item->data(Qt::UserRole+2).toString());
//                    xmlWriter.writeTextElement("Image", item->data(Qt::UserRole).toString());
//                    xmlWriter.writeTextElement("Type", item->data(Qt::UserRole+3).toString());
//                    xmlWriter.writeEndElement();

//                    tileCount++;
//                }
//        }


//        xmlWriter.writeEndDocument();
//        file.close();

//    }

}
