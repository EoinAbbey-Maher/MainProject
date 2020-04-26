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

	XMLElement* root = doc.FirstChildElement();

	XMLText* NoOfTextures = root->FirstChildElement("Map_Values")->FirstChildElement("NoOfTextures")->FirstChild()->ToText();
	XMLText* TotalTilesXml = root->FirstChildElement("Map_Values")->FirstChildElement("TotalTiles")->FirstChild()->ToText();
	XMLText* mapHeightXml = root->FirstChildElement("Map_Values")->FirstChildElement("RowSize")->FirstChild()->ToText();
	XMLText* mapWidthXml = root->FirstChildElement("Map_Values")->FirstChildElement("ColSize")->FirstChild()->ToText();


	int noOfTextureInt = std::stoi(NoOfTextures->Value());
	int TotalTilesInt = std::stoi(TotalTilesXml->Value());
	m_mapHeight = std::stoi(mapHeightXml->Value());
	m_mapWidth = std::stoi(mapWidthXml->Value());

	m_maxTiles = TotalTilesInt;

	for (int i = 0; i < noOfTextureInt; i++)
	{
		std::string str = "Texture" + std::to_string(i);
		char texturearr[11] = {};

		strcpy_s(texturearr, str.c_str());

		XMLText* ImageLink = root->FirstChildElement("Map_Values")->FirstChildElement(texturearr)->FirstChild()->ToText();

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


			XMLText* indexX = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexX")->FirstChild()->ToText();
			XMLText* indexY = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexY")->FirstChild()->ToText();
			XMLText* PositionX = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionX")->FirstChild()->ToText();
			XMLText* PositionY = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionY")->FirstChild()->ToText();
			XMLText* TypeXML = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("Type")->FirstChild()->ToText();

			XMLText* ImageURL = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("Image")->FirstChild()->ToText();

			std::string imgStr = ImageURL->Value();
			std::string typeStr = TypeXML->Value();

			Tile tile;


			if (typeStr == "Node")
			{
				tile.m_type = TileType::NODE;
			}
			else if (typeStr == "Wall")
			{
				tile.m_type = TileType::WALL;
			}
			else if (typeStr == "Floor")
			{
				tile.m_type = TileType::FLOOR;
			}
			else if (typeStr == "empty")
			{
				tile.m_type = TileType::EMPTY;
			}


			tile.indexPosition = sf::Vector2i(std::stoi(indexX->Value()), std::stoi(indexY->Value()));
			tile.m_position = sf::Vector2f(std::stof(PositionX->Value()), std::stof(PositionY->Value()));
			tile.m_ImgAddress = imgStr;

			tile.init(m_textureDict);

			m_tiles.push_back(tile);

			t++;
		} // !for j

	} // !for i


	std::cout << "builder" << std::endl;
	
}

void RoomBuilder::loadFile(const char* t_roomName, std::vector<Enemy>& t_enemies, Player& t_player)
{
/// ------------------------------------------------------------------------------
/// 
///									Build Main Room
/// 
/// ------------------------------------------------------------------------------
	emptyRoom();

	XMLDocument doc;
	doc.LoadFile(t_roomName);
	
	XMLElement* root = doc.FirstChildElement();

	XMLText* NoOfTextures = root->FirstChildElement("Map_Values")->FirstChildElement("NoOfTextures")->FirstChild()->ToText();
	XMLText* TotalTilesXml = root->FirstChildElement("Map_Values")->FirstChildElement("TotalTiles")->FirstChild()->ToText();
	XMLText* mapHeightXml = root->FirstChildElement("Map_Values")->FirstChildElement("RowSize")->FirstChild()->ToText();
	XMLText* mapWidthXml = root->FirstChildElement("Map_Values")->FirstChildElement("ColSize")->FirstChild()->ToText();


	int noOfTextureInt = std::stoi(NoOfTextures->Value());
	int TotalTilesInt = std::stoi(TotalTilesXml->Value());
	m_mapHeight = std::stoi(mapHeightXml->Value());
	m_mapWidth = std::stoi(mapWidthXml->Value());

	m_maxTiles = TotalTilesInt;

	for (int i = 0; i < noOfTextureInt; i++)
	{
		std::string str = "Texture" + std::to_string(i);
		char texturearr[11] = {};

		strcpy_s(texturearr, str.c_str());

		XMLText* ImageLink = root->FirstChildElement("Map_Values")->FirstChildElement(texturearr)->FirstChild()->ToText();

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


			XMLText* indexX = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexX")->FirstChild()->ToText();
			XMLText* indexY = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexY")->FirstChild()->ToText();
			XMLText* PositionX = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionX")->FirstChild()->ToText();
			XMLText* PositionY = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionY")->FirstChild()->ToText();
			XMLText* TypeXML = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("Type")->FirstChild()->ToText();

			XMLText* ImageURL = root->FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("Image")->FirstChild()->ToText();

			std::string imgStr = ImageURL->Value();
			std::string typeStr = TypeXML->Value();

			Tile tile;


			if (typeStr == "Node")
			{
				tile.m_type = TileType::NODE;
			}
			else if (typeStr == "Wall")
			{
				tile.m_type = TileType::WALL;
			}
			else if (typeStr == "Floor")
			{
				tile.m_type = TileType::FLOOR;
			}
			else if (typeStr == "empty")
			{
				tile.m_type = TileType::EMPTY;
			}


			tile.indexPosition = sf::Vector2i(std::stoi(indexX->Value()), std::stoi(indexY->Value()));
			tile.m_position = sf::Vector2f(std::stof(PositionX->Value()), std::stof(PositionY->Value()));
			tile.m_ImgAddress = imgStr;

			tile.init(m_textureDict);

			m_tiles.push_back(tile);

			t++;
		} // !for j

	} // !for i

	/// ------------------------------------------------------------------------------
	/// 
	///							Insert NPC Nodes and Player
	/// 
	/// ------------------------------------------------------------------------------


	XMLText* NoOfNodesXML = root->FirstChildElement("Nodes")->FirstChildElement("NoOfNodes")->FirstChild()->ToText();
	int NoOfNodesInt = std::stoi(NoOfNodesXML->Value());

	t_enemies.clear();
	for (int n = 0; n < NoOfNodesInt; n++)
	{
	
		std::string str = "Node" + std::to_string(n);
		char nodearr[10] = {};

		strcpy_s(nodearr, str.c_str());

		XMLText* indexX = root->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("IndexX")->FirstChild()->ToText();
		XMLText* indexY = root->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("IndexY")->FirstChild()->ToText();
		XMLText* PositionX = root->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("PositionX")->FirstChild()->ToText();
		XMLText* PositionY = root->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("PositionY")->FirstChild()->ToText();
		XMLText* TypeXML = root->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("Type")->FirstChild()->ToText();

		XMLText* ImageURL = root->FirstChildElement("Nodes")->FirstChildElement(nodearr)->FirstChildElement("Image")->FirstChild()->ToText();


		std::string imgStr = ImageURL->Value();
		std::string typeStr = TypeXML->Value();

		if (imgStr == "playerNode")
		{
			t_player.m_position = sf::Vector2f(std::stof(PositionX->Value()) + t_player.m_size.x, std::stof(PositionY->Value()) + t_player.m_size.y);
		}
		else if (imgStr == "NPCNode")
		{
			Enemy* enem = new Enemy;

			enem->init(new sf::Texture(), sf::Vector2f(std::stof(PositionX->Value() ) +20, std::stof(PositionY->Value()) + 20));
			t_enemies.push_back(*enem);
		}


		//m_tiles[i][j].indexPosition = sf::Vector2i(std::stoi(indexX->Value()), std::stoi(indexY->Value()));
		//m_tiles[i][j].m_position = sf::Vector2f(std::stof(PositionX->Value()), std::stof(PositionY->Value()));
		//m_tiles[i][j].m_ImgAddress = imgStr;

		//m_tiles[i][j].init(m_textureDict);

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
			m_tiles.clear();
		} // !for j
	
	} // !for i

} // !emptyRoom

void RoomBuilder::render()
{
	int t = 0;
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			m_tiles[t].render(m_window);
			t++;
		} // !for j

	} // !for i

} // !render
