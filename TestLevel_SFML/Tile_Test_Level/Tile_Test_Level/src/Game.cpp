
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ GlobalSettings::s_width, GlobalSettings::s_height, 32U }, "Jigsaw Level Builder Demo", sf::Style::Default },
	m_roombuilder{m_window},
	m_exitGame{false},
	m_Player(m_window)
{
	m_roombuilder.loadFile("assets\\MapExport\\Map_Data.xml", m_enemies, m_Player);
	
	
	sf::Texture	enemyTexture;
	if (!enemyTexture.loadFromFile("assets\\IMAGES\\invader.png"))
	{
		std::cout << "failed to load " << std::endl;
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].setTexture(&enemyTexture);
	}

}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);

		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	m_Player.processGameEvents(t_event);
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	m_Player.update(t_deltaTime, m_roombuilder);


	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].update(m_roombuilder, m_Player);
	}
	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_roombuilder.render();
	m_Player.render();
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i].render(m_window);
	}
	m_window.display();
}
