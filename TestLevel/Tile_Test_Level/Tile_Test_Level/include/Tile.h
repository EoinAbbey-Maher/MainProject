#ifndef TILE
#define TILE

#include "Global.h"

enum class TileType
{
	FLOOR,
	WALL,
	DOOR,
	EMPTY
};

class Tile
{
public: //functions
	Tile();

	~Tile();
	void render(sf::RenderWindow & t_window);

	void init(std::map<std::string, sf::Texture*> & t_texturesMap);
	void setTexture(sf::Texture & t_texture);

private: //functions


public: //variables
	
	sf::RectangleShape m_bodySquare;
	std::string m_ImgAddress;

	sf::Vector2i indexPosition;
	sf::Vector2f m_position{ 0,0 };
private: //variables 
	
	sf::IntRect m_textureRect;
	int const M_SIZE{ 32};

	
};

#endif // !TILE