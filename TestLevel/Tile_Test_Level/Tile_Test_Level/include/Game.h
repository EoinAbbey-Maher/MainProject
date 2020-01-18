#ifndef GAME_HPP
#define GAME_HPP

//SDKs
#include <SFML/Graphics.hpp>
#include <vector>


//User Files
#include "RoomBuilder.h"

class Game
{
public:
	Game();
	~Game();
	void run();

public: //Variables

private: //Functions
	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupSprite();
	RoomBuilder m_roombuilder;

private: //Variables

	sf::RenderWindow m_window; // main SFML window

	bool m_exitGame; // control exiting game
};

#endif // !GAME_HPP

