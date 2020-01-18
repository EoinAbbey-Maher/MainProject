#ifndef ROOMBUILDER
#define ROOMBUILDER

#include "Tile.h"
#include "tinyxml2.h"
#include <fstream>

using namespace tinyxml2;

class RoomBuilder
{
public: // functions
	RoomBuilder(sf::RenderWindow & t_window);
	~RoomBuilder();
	
	void loadFile(const char* t_roomName);

	void loadAssets();
	void render();

private: // functions
	void emptyRoom();

public: // variables

	static const int M_TOTALHEIGHT = 20;
	static const int M_TOTALWIDTH = 32;

	Tile m_tiles[M_TOTALHEIGHT][M_TOTALWIDTH];
	
private: //variables
	const int MAX_TEXTURES{ 6 };
	int m_tileValue[M_TOTALHEIGHT][M_TOTALWIDTH];
	std::vector<sf::Texture> m_textures;

	sf::RenderWindow & m_window;


	sf::Texture floor1;
	sf::Texture floor2;
	sf::Texture wall1;
	sf::Texture wall2;
	sf::Texture door1;
	sf::Texture star;

};

#endif // !ROOMBUILDER
