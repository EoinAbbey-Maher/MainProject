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
	emptyRoom();

	XMLDocument doc;
	doc.LoadFile(t_roomName);

	XMLText * NoOfTextures = doc.FirstChildElement("Map_Values")->FirstChildElement("NoOfTextures")->FirstChild()->ToText();
	XMLText* TotalTilesXml= doc.FirstChildElement("Map_Values")->FirstChildElement("TotalTiles")->FirstChild()->ToText();
	

	int noOfTextureInt = std::stoi(NoOfTextures->Value());
	int TotalTilesInt= std::stoi(TotalTilesXml->Value());
	

	for (int i = 0; i < noOfTextureInt; i++)
	{
		std::string str = "Texture" + std::to_string(i);
		char texturearr[11] = {};

		strcpy_s(texturearr, str.c_str());

		XMLText* ImageLink = doc.FirstChildElement("Map_Values")->FirstChildElement(texturearr)->FirstChild()->ToText();
		std::string imageString = ImageLink->Value();
		imageString = imageString.erase(0, 2);

		m_textureAddresses.push_back(imageString);

		m_textures.push_back(sf::Texture());
		
		if (!m_textures[i].loadFromFile("assets\\Tiles\\" + imageString))
		{
			std::cout << "failed to load " << std::endl;
		}


		m_textureDict[imageString] = &m_textures[i];
	}
	
	int t = 0;

	for (int i = 0; i < M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j < M_TOTALWIDTH; j++)
		{
			
			std::string str = "Tile" + std::to_string(t);
			char tilearr[10] = {};

			strcpy_s(tilearr, str.c_str());
			

			XMLText* indexX = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexX")->FirstChild()->ToText();
			XMLText* indexY = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("IndexY")->FirstChild()->ToText();
			XMLText* PositionX = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionX")->FirstChild()->ToText();
			XMLText* PositionY = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionY")->FirstChild()->ToText();
			XMLText* TypeXML = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("PositionY")->FirstChild()->ToText();

			XMLText* ImageURL = doc.FirstChildElement("Tiles")->FirstChildElement(tilearr)->FirstChildElement("Image")->FirstChild()->ToText();
			
			std::string imgStr =ImageURL->Value();
			imgStr = imgStr.erase(0, 2);

			m_tiles[i][j].indexPosition = sf::Vector2i(std::stoi(indexX->Value()), std::stoi(indexY->Value()));
			m_tiles[i][j].m_position = sf::Vector2f(std::stof(PositionX->Value()), std::stof(PositionY->Value()));
			m_tiles[i][j].m_ImgAddress = imgStr;

			m_tiles[i][j].init(m_textureDict);


			t++;
		} // !for j

	} // !for i


	


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
