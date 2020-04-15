#ifndef PLAYER_H
#define PLAYER_H

//SDKs
#include <SFML/Graphics.hpp>

// User Files
#include "RoomBuilder.h"
#include "Global.h"

static const float RADIANSVAL{ 3.14 / 180 };
static const float MAXPLAYERVELOCITY{ 5 };

class Player
{
public: //Functions
	Player(sf::RenderWindow & t_window);
	~Player();

	void update(sf::Time t_td, RoomBuilder& t_rb);
	void render();
	void processGameEvents(sf::Event t_e);

	void move(float t_accel);
	void turn(float t_accel);

	void checkBoundaries(RoomBuilder& t_roombuilder);

public : //Variables
	sf::Vector2f m_position{ 0,0};
	sf::Vector2f m_lastPosition;
	sf::Vector2f m_size{ 37,25 };
	sf::Vector2f m_velocity{ 1,10 };
	
	float m_orientation{ 90 };

private: //Functions
	void setupBody();

private: //Variables
	float m_acceleration{ .5 };
	
	sf::RectangleShape m_bodyShape;
	sf::Texture m_texure;
	sf::Texture m_accelTexture;
	sf::RenderWindow& m_window;



};

#endif // !PLAYER_H

