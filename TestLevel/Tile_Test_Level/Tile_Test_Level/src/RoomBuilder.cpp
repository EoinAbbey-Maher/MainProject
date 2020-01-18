#include "RoomBuilder.h"

RoomBuilder::RoomBuilder(sf::RenderWindow & t_window) :
	m_window(t_window)
{
	loadAssets();
	
	for (int i = 0; i < M_TOTALHEIGHT; i++)
	{
		for (int j = 0; j  < M_TOTALWIDTH; j++)
		{			
			m_tiles[i][j].init(sf::Vector2f(0, 0),&floor1, &floor2, &wall1, &wall2, &door1, &star);						
		} // !for j
		
	} // !for i
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

	XMLText* indexX = doc.FirstChildElement("Tiles")->FirstChildElement("Tile0")->FirstChildElement("IndexX")->FirstChild()->ToText();
	XMLText* indexY= doc.FirstChildElement("Tiles")->FirstChildElement("Tile0")->FirstChildElement("IndexY")->FirstChild()->ToText();
	XMLText*  Position = doc.FirstChildElement("Tiles")->FirstChildElement("Tile0")->FirstChildElement("Position")->FirstChild()->ToText();
	XMLText* ImageURL = doc.FirstChildElement("Tiles")->FirstChildElement("Tile0")->FirstChildElement("Image")->FirstChild()->ToText();

	std::string imageString = ImageURL->Value();
	imageString = imageString.erase(0,2);

	std::cout << indexX->Value() << std::endl;
	std::cout << indexY->Value() << std::endl;
	std::cout << Position->Value() << std::endl;
	std::cout << imageString << std::endl;


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
