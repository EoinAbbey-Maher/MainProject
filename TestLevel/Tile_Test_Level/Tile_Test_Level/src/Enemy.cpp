#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::init(sf::Texture* t_texture, sf::Vector2f t_position)
{
	m_position = t_position;
	m_body.setTexture(t_texture);
	m_body.setPosition(t_position);
	m_body.setSize(m_size);
	m_body.setOrigin(m_size.x * .5, m_size.y * .5);
}

void Enemy::update(RoomBuilder& t_room, Player& t_player)
{
}

void Enemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}
