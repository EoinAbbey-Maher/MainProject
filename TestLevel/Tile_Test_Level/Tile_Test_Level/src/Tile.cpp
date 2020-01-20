#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::init( std::map<std::string, sf::Texture*>& t_texturesMap)
{
	m_bodySquare.setTexture(t_texturesMap["floor.png"]);

	m_bodySquare.setPosition(m_position);
	m_bodySquare.setSize(sf::Vector2f(M_SIZE, M_SIZE));
}

void Tile::setTexture(sf::Texture& t_texture)
{
	m_bodySquare.setTexture(&t_texture);
}

////void Tile::setTexture(TileType t_type, const int T_XPOS, const int T_YPOS)
////{
////	int randomNum;
////	randomNum = std::rand() % 2;
////	switch (t_type)
////	{
////	case TileType::FLOOR:
////		switch (randomNum)
////		{
////		case 0:
////			m_bodySquare.setTexture(m_textureDict["floor_1"]);
////			break;
////		case 1:
////			m_bodySquare.setTexture(m_textureDict["floor_2"]);
////			break;
////		default:
////			break;
////		} // !case FLOOR
////		break;
////		m_type = t_type;
////	case TileType::WALL:
////		switch (randomNum)
////		{
////		case 0:
////			m_bodySquare.setTexture(m_textureDict["wall_1"]);
////			break;
////		case 1:
////			m_bodySquare.setTexture(m_textureDict["wall_2"]);
////			break;
////		default:
////			break;
////		} // !case WALL
////		m_type = t_type;
////		break;
////	case TileType::DOOR:
////		switch (randomNum)
////		{
////		case 0:
////			m_bodySquare.setTexture(m_textureDict["door_open"]);
////			break;
////		default:
////			break;
////		} // !DOOR
////		m_type = t_type;
////		break;
////	case TileType::EMPTY:
////		m_bodySquare.setTexture(m_textureDict["star_tile"]);
////		m_type = t_type;
////		break;
////	default:
////		break;
////	} // !Switch
////
////	m_position = sf::Vector2f(M_SIZE * T_XPOS, M_SIZE * T_YPOS);
////	m_bodySquare.setPosition(m_position);
////	
////}
////// !setTexture

void Tile::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_bodySquare);
} // !render
