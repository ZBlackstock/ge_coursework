#include <SFML/Graphics.hpp>
#include <string>
#include "Engine\RenderMan.h"
#include "Engine\SceneMan.hpp"
#include "Engine\Scene.hpp"
#include "Engine\game_system.h"

sf::Vector2i GameSystem::screen_size = sf::Vector2i{ 1000,1000 };
sf::Vector2f GameSystem::screen_size_f = static_cast<sf::Vector2f>(GameSystem::screen_size);
std::string GameSystem::sprites_path = "../res/sprites/";

int main() {
	sf::RenderWindow window(sf::VideoMode(GameSystem::screen_size.x, GameSystem::screen_size.y), "SFML Test");

	RenderMan::SetWindow(&window);
	SceneManager::init();

	while (window.isOpen()) {
		RenderMan::RenderWindowClear();
		sf::Event event;

		static sf::Clock clock;
		const float dt = clock.restart().asSeconds();

		SceneManager::update(dt);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		RenderMan::RenderWindow();
	}
	return 0;
}

