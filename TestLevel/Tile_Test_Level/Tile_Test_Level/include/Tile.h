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

	void init(sf::Vector2f t_pos, 
		sf::Texture * t_floor1, 
		sf::Texture * t_floor2, 
		sf::Texture * t_wall1, 
		sf::Texture * t_wall2, 
		sf::Texture * t_doorOpen, 
		sf::Texture * t_doorClosed);

	void setTexture(sf::Texture & t_texture);

private: //functions


public: //variables
	std::map<std::string,sf::Texture*> m_textureDict;
	
	sf::RectangleShape m_bodySquare;
	std::string m_type;

	sf::Vector2i indexPosition;
	sf::Vector2f m_position{ 0,0 };
private: //variables 
	
	sf::IntRect m_textureRect;
	int const M_SIZE{ 32};

	
};

#endif // !TILE