#include <iostream>
#include "game_system.hpp"
#include "..\SceneMan.hpp"
#include "..\input_man.hpp"
#include "renderer.hpp"

using gs = GameSystem;

void GameSystem::start(unsigned int width, unsigned int height, const std::string& name, const float& time_step, bool physics_enabled)
{
	GameSystem::assign_paths();
	sf::RenderWindow window(sf::VideoMode(width, height), "Black Dragon", sf::Style::Fullscreen);
	RenderMan::SetWindow(&window);
	sf::Event event;

	while (window.isOpen())
	{
		static sf::Clock clock;
		float dt = clock.restart().asSeconds();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return;
			}
		}

		RenderMan::RenderWindowClear();
		_update(dt);
		sf::sleep(sf::seconds(time_step));
		_render();
	}
	window.close();
}

void GameSystem::_update(const float& dt)
{
	SceneManager::update(dt);
	EventManager::update(dt);
	InputManager::Update(dt);
}

void GameSystem::_render()
{
	RenderMan::RenderWindow();
}

void GameSystem::assign_paths()
{
	if (!gs::font.loadFromFile("../../../../res/fonts/COPRGTL.ttf"))
	{
		std::cout << "Couldnt load font" << std::endl;
	}

	if (!gs::font_bold.loadFromFile("../../../../res/fonts/COPRGTB.ttf"))
	{
		std::cout << "Couldnt load font_bold" << std::endl;
	}
}