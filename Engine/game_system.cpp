#include <iostream>
#include "game_system.hpp"
#include "..\SceneMan.hpp"
#include "..\input_man.hpp"
#include "..\fight_manager.hpp"
#include "RenderMan.h"
#include "AudioManager.h"

using gs = GameSystem;
EntityManager GameSystem::_entities;
using am = AudioManager;

void GameSystem::start(unsigned int width, unsigned int height, const std::string& name, const float& time_step, bool physics_enabled)
{
	GameSystem::assign_paths();
	sf::RenderWindow window(sf::VideoMode(width, height), "Black Dragon", sf::Style::Fullscreen);

	RenderMan::SetWindow(&window);
	sf::Event event;
	InputManager::init();
	am::addMusic("main_menu_theme");

	sf::View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view);

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

const std::shared_ptr<Entity>& GameSystem::make_entity() {
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	_entities.list.push_back(entity);
	return _entities.list.back();
}