#include "include/xmlwriter.h"
#include "include/mainwindow.h"
#include "ui_mainwindow.h"


XMLWriter::XMLWriter()
{

}

/// -------------------------------------------------------------------------------------------------------------------
///
///                                         Writing Data into new XML File
///
/// -------------------------------------------------------------------------------------------------------------------

void XMLWriter::WriteTilesToFile(QTableWidget *t_table,QTableWidget * t_nodeTable, QVector<QPair<QString,QString>> t_TextureNames)
{

    /// -------------------------------------------------------------------------------------------------------------------
    ///
    ///                                             Setting Up Folder save locations
    ///
    /// -------------------------------------------------------------------------------------------------------------------
    QString fileName = m_XML_Name;

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


    /// -------------------------------------------------------------------------------------------------------------------
    ///
    ///                                             Exporting Textures to Folder
    ///
    /// -------------------------------------------------------------------------------------------------------------------

     QFile file(path + fileName);
    if(file.open(QIODevice::WriteOnly))
     {

        QXmlStreamWriter xmlWriter(&file);

        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

        xmlWriter.writeStartElement("Map_Export");
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


        /// -------------------------------------------------------------------------------------------------------------------
        ///
        ///                                             Exporting All Tile Information
        ///
        /// -------------------------------------------------------------------------------------------------------------------
        int tileCount = 0;
        for (int r = 0; r < t_table->rowCount(); r++)
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

         xmlWriter.writeEndElement();


         /// -------------------------------------------------------------------------------------------------------------------
         ///
         ///                                             Exporting All Node Information
         ///
         /// -------------------------------------------------------------------------------------------------------------------
         xmlWriter.writeStartElement("Nodes");
        int nodeCount = 0;
        for (int r = 0; r < t_nodeTable ->rowCount(); r++)
           {
               for (int c = 0; c < t_nodeTable ->columnCount(); c++)
                {
                   QTableWidgetItem * nodeItem = t_nodeTable->item(r,c);

                   if(nodeItem->data(Qt::UserRole) != "empty")
                   {
                    xmlWriter.writeStartElement("Node" + QString::number(nodeCount));
                    xmlWriter.writeTextElement("IndexX", QString::number(c));
                    xmlWriter.writeTextElement("IndexY", QString::number(r));
                    xmlWriter.writeTextElement("PositionX",nodeItem->data(Qt::UserRole+1).toString());
                    xmlWriter.writeTextElement("PositionY",nodeItem->data(Qt::UserRole+2).toString());
                    xmlWriter.writeTextElement("Image", nodeItem->data(Qt::UserRole).toString());
                    xmlWriter.writeTextElement("Type", nodeItem->data(Qt::UserRole+3).toString());
                    xmlWriter.writeEndElement();
                    nodeCount++;

                   }
                }
        }

        xmlWriter.writeTextElement("NoOfNodes", QString::number(nodeCount));
        xmlWriter.writeEndElement();
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

/// -------------------------------------------------------------------------------------------------------------------
///
///                                                  Load In Existing File
///
/// -------------------------------------------------------------------------------------------------------------------
void XMLWriter::ReadExistingFile()
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

    QDomElement root = xmlDoc.firstChildElement("Map_Export");
    QDomElement mapValues = root.firstChildElement("Map_Values");
    QDomText noOfTexturesXML = mapValues.firstChildElement("NoOfTextures").firstChild().toText();
    QDomText TotalTilesXML = mapValues.firstChildElement("TotalTiles").firstChild().toText();
    QDomText mapheightXML= mapValues.firstChildElement("RowSize").firstChild().toText();
    QDomText mapWidthXML = mapValues.firstChildElement("ColSize").firstChild().toText();

    int noOFTexturesInt = noOfTexturesXML.data().toInt();
    int TotalTilesInt = TotalTilesXML.data().toInt();
    int mapHeightInt = mapheightXML.data().toInt();
    int mapWidthInt = mapWidthXML.data().toInt();

    MainWindow* mainWindow = new MainWindow(mapHeightInt, mapWidthInt);

    QVector<QPair<QString, QImage*>> name_ImagePair;

    mainWindow->m_texturePair.clear();


    /// ------------------------------------------------------------------------------------------------------------------
    ///
    ///                                             Loading in all the textures
    ///
    /// ------------------------------------------------------------------------------------------------------------------

    for(int i = 0; i < noOFTexturesInt; i++)
    {
        QString str = "Texture" + QString::number(i);
        char textureArr[11] = {};
        strcpy(textureArr, str.toStdString().c_str());

        QDomText ImageLink = mapValues.firstChildElement(textureArr).firstChild().toText();

        mainWindow->m_texturePair.push_back(QPair<QString, QString>(folderPath + "/Images/" + ImageLink.data() + ".png",ImageLink.data()));

        QImage * image = new QImage();
        if(!image->load(mainWindow->m_texturePair[i].first))
        {
            qDebug("failed to load image");
        }

        name_ImagePair.push_back(QPair<QString, QImage*>((mainWindow->m_texturePair[i].second),image));
    }

    QTableWidget * table = mainWindow->m_mapTable;
    int  t = 0;

    /// ------------------------------------------------------------------------------------------------------------------
    ///
    ///                                             Setting Up Tiles
    ///
    /// ------------------------------------------------------------------------------------------------------------------

    QDomElement tilesRoot = root.firstChildElement("Tiles");

    for (int r = 0; r < mapHeightInt; r++) {
        for (int c = 0; c < mapWidthInt; c++) {

            QString tilestr = "Tile" + QString::number(t);

            QString ImageTagString = tilesRoot.firstChildElement(tilestr).firstChildElement("Image").firstChild().nodeValue();
            int PositionXInt = tilesRoot.firstChildElement(tilestr).firstChildElement("PositionX").firstChild().nodeValue().toInt();
            int PositionYInt = tilesRoot.firstChildElement(tilestr).firstChildElement("PositionY").firstChild().nodeValue().toInt();
            QString TypeTagString = tilesRoot.firstChildElement(tilestr).firstChildElement("Type").firstChild().nodeValue();

            TileItem* item = new TileItem;
            for (int i= 0; i< name_ImagePair.size(); i++) {
                if(name_ImagePair[i].first == ImageTagString)
                {
                    item->setData(Qt::DecorationRole, QPixmap::fromImage(*name_ImagePair[i].second));
                    break;
                }
            }
            item->setData(Qt::UserRole, ImageTagString);
            item->setData(Qt::UserRole+1, PositionXInt);
            item->setData(Qt::UserRole+2, PositionYInt);
            item->setData(Qt::UserRole+3, TypeTagString);
            table->setItem(r,c,item);

            t++;
        }
    }


    /// ------------------------------------------------------------------------------------------------------------------
    ///
    ///                                             Setting Up Nodes
    ///
    /// ------------------------------------------------------------------------------------------------------------------

     QTableWidget * nodetable = mainWindow->m_NodeTable;

    QDomElement NodesRoot = root.firstChildElement("Nodes");
    int n = 0;
    int noOfNodes = NodesRoot.firstChildElement("NoOfNodes").firstChild().nodeValue().toInt();
            for(int i = 0; i <  noOfNodes; i++)
            {
            QString nodestr = "Node" + QString::number(i);

            QString ImageTagString = NodesRoot.firstChildElement(nodestr).firstChildElement("Image").firstChild().nodeValue();
            int IndexXInt = NodesRoot.firstChildElement(nodestr).firstChildElement("IndexX").firstChild().nodeValue().toInt();
            int IndexYInt = NodesRoot.firstChildElement(nodestr).firstChildElement("IndexY").firstChild().nodeValue().toInt();
            int PositionXInt = NodesRoot.firstChildElement(nodestr).firstChildElement("PositionX").firstChild().nodeValue().toInt();
            int PositionYInt = NodesRoot.firstChildElement(nodestr).firstChildElement("PositionY").firstChild().nodeValue().toInt();
            QString TypeTagString = NodesRoot.firstChildElement(nodestr).firstChildElement("Type").firstChild().nodeValue();

            TileItem* item = new TileItem;
            for (int i= 0; i< name_ImagePair.size(); i++) {
                if(name_ImagePair[i].first == ImageTagString)
                {
                    item->setData(Qt::DecorationRole, QPixmap::fromImage(*name_ImagePair[i].second).scaled(50,50));
                    break;
                }
            }
            item->setData(Qt::UserRole, ImageTagString);
            item->setData(Qt::UserRole+1, PositionXInt);
            item->setData(Qt::UserRole+2, PositionYInt);
            item->setData(Qt::UserRole+3, TypeTagString);
            nodetable->setItem(IndexYInt,IndexXInt,item);

            n++;
            }

    //close();
    mainWindow->show();
}
