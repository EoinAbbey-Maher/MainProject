#include "RoomBuilder.h"

RoomBuilder::RoomBuilder(sf::RenderWindow & t_window) :
	m_window(t_window)
{
}

RoomBuilder::~RoomBuilder()
{
} // !~RoomBuilder

/// <summary>
/// Function to load the room layout txt file
/// </summary>
/// <param name="t_roomName">file name</param>
void RoomBuilder::loadFile(const char* t_roomName)
{

	/// ------------------------------------------------------------------------------
	/// 
	///									Build Main Room
	/// 
	/// ------------------------------------------------------------------------------
	emptyRoom();

	XMLDocument doc;
	doc.LoadFile(t_roomName);

	XMLText * NoOfTextures = doc.FirstChildElement("Map_Export")->FirstChildElement("Map_Values")->FirstChildElement("NoOfTextures")->FirstChild()->ToText();
	XMLText* TotalTilesXml= doc.FirstChildElement("Map_Export")->FirstChildElement("Map_Values")->FirstChildElement("TotalTiles")->FirstChild()->ToText();
	XMLText* mapHeightXml = doc.FirstChildElement("Map_Export")->FirstChildElement("Map_Values")->FirstChildElement("RowSize")->FirstChild()->ToText();
	XMLText* mapWidthXml = doc.FirstChildElement("Map_Export")->FirstChildElement("Map_Values")->FirstChildElement("ColSize")->FirstChild()->ToText();
	

	int noOfTextureInt = std::stoi(NoOfTextures->Value());
	int TotalTilesInt= std::stoi(TotalTilesXml->Value());
	m_mapHeight = std::stoi(mapHeightXml->Value());
	m_mapWidth = std::stoi(mapWidthXml->Value());

	m_maxTiles = TotalTilesInt;

	for (int i = 0; i < noOfTextureInt; i++)
	{
		std::string str = "Texture" + std::to_string(i);
		char texturearr[11] = {};

		strcpy_s(texturearr, str.c_str());

		XMLText* ImageLink = doc.FirstChildElement("Map_Export")->FirstChildElement("Map_Values")->FirstChildElement(texturearr)->FirstChild()->ToText();

		m_textureAddresses.push_back(ImageLink->Value());

		m_textures.push_back(sf::Texture());
		
		if (!m_textures[i].loadFromFile("assets\\MapExport\\Images\\" + m_textureAddresses[i] + ".png"))
		{
			std::cout << "failed to load " << std::endl;
		}


		m_textureDict[m_textureAddresses[i]] = m_textures[i];
	}
	
	int t = 0;

	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			
			std::string str = "Tile" + std::to_string(t);
			char tilearr[10] = {};

			strcpy_s(tilearr, str.c_str());
			

			XMLText* indexX = doc.FirstChildElement("Map_Export")->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexX")->FirstChild()->ToText();
			XMLText* indexY = doc.FirstChildElement("Map_Export")->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexY")->FirstChild()->ToText();
			XMLText* PositionX = doc.FirstChildElement("Map_Export")->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionX")->FirstChild()->ToText();
			XMLText* PositionY = doc.FirstChildElement("Map_Export")->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionY")->FirstChild()->ToText();
			XMLText* TypeXML = doc.FirstChildElement("Map_Export")->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("Type")->FirstChild()->ToText();

			XMLText* ImageURL = doc.FirstChildElement("Map_Export")->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("Image")->FirstChild()->ToText();
			
			std::string imgStr = ImageURL->Value();
			std::string typeStr = TypeXML->Value();
			
			if (typeStr == "Node")
			{
				m_tiles[i][j].m_type = TileType::NODE;
			}
			else if (typeStr == "Wall")
			{
				m_tiles[i][j].m_type = TileType::WALL;
			}
			else if (typeStr == "Floor")
			{
				m_tiles[i][j].m_type = TileType::FLOOR;
			}
			else if (typeStr == "empty")
			{
				m_tiles[i][j].m_type = TileType::EMPTY;
			}


			m_tiles[i][j].indexPosition = sf::Vector2i(std::stoi(indexX->Value()), std::stoi(indexY->Value()));
			m_tiles[i][j].m_position = sf::Vector2f(std::stof(PositionX->Value()), std::stof(PositionY->Value()));
			m_tiles[i][j].m_ImgAddress = imgStr;

			m_tiles[i][j].init(m_textureDict);

			t++;
		} // !for j

	} // !for i

	/// ------------------------------------------------------------------------------
	/// 
	///							Insert NPC Nodes and Player
	/// 
	/// ------------------------------------------------------------------------------

	
	XMLText* NoOfNodesXML = doc.FirstChildElement("Map_Export")->FirstChildElement("Nodes")->FirstChildElement("NoOfNodes")->FirstChild()->ToText();
	int NoOfNodesInt = std::stoi(NoOfNodesXML->Value());

	for (int n = 0; n < NoOfNodesInt; n++)
	{
		std::string str = "Node" + std::to_string(t);
		char nodearr[10] = {};

		strcpy_s(nodearr, str.c_str());

		XMLText* indexX = doc.FirstChildElement("Map_Export")->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("IndexX")->FirstChild()->ToText();
		XMLText* indexY = doc.FirstChildElement("Map_Export")->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("IndexY")->FirstChild()->ToText();
		XMLText* PositionX = doc.FirstChildElement("Map_Export")->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("PositionX")->FirstChild()->ToText();
		XMLText* PositionY = doc.FirstChildElement("Map_Export")->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("PositionY")->FirstChild()->ToText();
		XMLText* TypeXML = doc.FirstChildElement("Map_Export")->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("Type")->FirstChild()->ToText();

		XMLText* ImageURL = doc.FirstChildElement("Map_Export")->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("Image")->FirstChild()->ToText();


		std::string imgStr = ImageURL->Value();
		std::string typeStr = TypeXML->Value();

		if (typeStr == "Node")
		{

		}
		else if (typeStr == "Wall")
		{
			m_tiles[i][j].m_type = TileType::WALL;
		}
		else if (typeStr == "Floor")
		{
			m_tiles[i][j].m_type = TileType::FLOOR;
		}
		else if (typeStr == "empty")
		{
			m_tiles[i][j].m_type = TileType::EMPTY;
		}


		m_tiles[i][j].indexPosition = sf::Vector2i(std::stoi(indexX->Value()), std::stoi(indexY->Value()));
		m_tiles[i][j].m_position = sf::Vector2f(std::stof(PositionX->Value()), std::stof(PositionY->Value()));
		m_tiles[i][j].m_ImgAddress = imgStr;

		m_tiles[i][j].init(m_textureDict);

		t++;
	}

	std::cout << "builder" << std::endl;

	
}

/// <summary>
/// Function to empty game room
/// </summary>
void RoomBuilder::emptyRoom()
{
	for (int i = 0; i < M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < M_TOTALWIDTH; j++)
		{

			m_tileValue[i][j] = 0;
		} // !for j
	
	} // !for i

} // !emptyRoom

/// <summary>
/// Function to load in tile assets and textures
/// </summary>
void RoomBuilder::loadAssets()
{
	if (floor1.loadFromFile("Assets\\IMAGES\\Floor1.png")) { std::cout << "loaded"; }
	if (floor2.loadFromFile("Assets\\IMAGES\\Floor2.png")) { std::cout << "loaded"; }
	if (wall1.loadFromFile("Assets\\IMAGES\\wall1.png")) { std::cout << "loaded"; }
	if (wall2.loadFromFile("Assets\\IMAGES\\wall2.png")) { std::cout << "loaded"; }
	if (star.loadFromFile("Assets\\IMAGES\\star.png")) { std::cout << "loaded"; }

} // !loadAssets

void RoomBuilder::render()
{
	for (int i = 0; i < M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < M_TOTALWIDTH; j++)
		{
			m_tiles[i][j].render(m_window);
		} // !for j

	} // !for i

} // !render
