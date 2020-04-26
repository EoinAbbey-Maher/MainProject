#ifndef ROOMBUILDER
#define ROOMBUILDER

#include "Tile.h"
#include "Enemy.h"
#include "tinyxml2.h"
#include <fstream>


using namespace tinyxml2;

class Enemy;
class Player;

class RoomBuilder
{
public: // functions
	RoomBuilder(sf::RenderWindow & t_window);
	~RoomBuilder();
	
	void loadFile(const char* t_roomName);
	void loadFile(const char* t_roomName, std::vector<Enemy> & t_enemies, Player & t_player);

	void render();

private: // functions
	void emptyRoom();

public: // variables

	std::map<std::string, sf::Texture> m_textureDict;

	int m_mapHeight = 0;
	int m_mapWidth = 0;

	static const int M_TOTALHEIGHT = 20;
	static const int M_TOTALWIDTH = 32;

	std::vector<Tile> m_tiles;

	int m_maxTiles;
	//Tile m_tiles[M_TOTALHEIGHT][M_TOTALWIDTH];
	sf::Vector2i m_tileSize = sf::Vector2i(50, 50);
private: //variables
	const int MAX_TEXTURES{ 6 };
	int m_tileValue[M_TOTALHEIGHT][M_TOTALWIDTH];
	std::vector<sf::Texture> m_textures;
	std::vector<sf::String> m_textureAddresses;
	   	 
	sf::Vector2f m_playerPos;
	std::vector<sf::Vector2f> m_NPCPositions;

	sf::RenderWindow & m_window;

	sf::Texture floor1;
	sf::Texture floor2;
	sf::Texture wall1;
	sf::Texture wall2;
	sf::Texture door1;
	sf::Texture star;

};

#endif // !ROOMBUILDER
