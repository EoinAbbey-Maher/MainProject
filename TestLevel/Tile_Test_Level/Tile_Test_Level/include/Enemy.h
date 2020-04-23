#ifndef Enemy_H
#define Enemy_H

#include <SFML/Graphics.hpp>

#include "Global.h"
#include "RoomBuilder.h"
#include "Player.h"

class RoomBuilder;
class Player;

class Enemy
{
public: // functions
	Enemy();
	~Enemy() {};

	void init(sf::Texture * t_texture, sf::Vector2f m_position);
	void setTexture(sf::Texture* t_texture);
	void update(RoomBuilder& m_room, Player& t_player);
	void render(sf::RenderWindow & t_window);

public: // variables

private: // functions

private: // variables

	sf::Vector2f m_position;
	sf::Vector2f m_lastPosition;
	sf::Vector2f m_size{ 40,40};

	sf::Texture m_texture;
	sf::RectangleShape m_body;
	
};


#endif // !SWEEPER_H


