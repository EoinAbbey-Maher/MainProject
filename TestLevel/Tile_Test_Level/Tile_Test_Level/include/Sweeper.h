#ifndef SWEEPER_H
#define SWEEPER_H

#include <SFML/Graphics.hpp>

#include "Global.h"
#include "RoomBuilder.h"
#include "Player.h"

class Sweeper
{
public: // functions
	Sweeper();
	~Sweeper() {};

	void init(sf::Texture * t_texture, sf::Vector2f m_position);
	
	void update(RoomBuilder& m_room, Player& t_player);
	void render(sf::RenderWindow & t_window);

public: // variables

private: // functions

private: // variables

	sf::Vector2f m_position;
	sf::Vector2f m_lastPosition;
	sf::Vector2f m_size{ 40,40};

	sf::RectangleShape m_body;
	
};


#endif // !SWEEPER_H


