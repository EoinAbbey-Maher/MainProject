#include "Tile.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::init( std::map<std::string, sf::Texture>& t_texturesMap)
{
	if (m_type == TileType::EMPTY || m_type == TileType::NODE)
	{
		m_bodySquare.setFillColor(sf::Color::Black);
	}
	m_bodySquare.setTexture(&t_texturesMap[m_ImgAddress]);

	m_bodySquare.setPosition(indexPosition.x * m_size, indexPosition.y * m_size);
	m_bodySquare.setSize(sf::Vector2f(50, 50));
}

void Tile::setTexture(sf::Texture& t_texture)
{
	m_bodySquare.setTexture(&t_texture);
}

void Tile::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_bodySquare);
} // !render
