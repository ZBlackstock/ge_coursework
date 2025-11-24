#include <SFML/Graphics.hpp>
#include <string>
#include "Engine\RenderMan.h"
#include "Engine\SceneMan.hpp"
#include "Engine\Scene.hpp"
#include "Engine\game_system.h"
#include "Engine\event_man.hpp"

using gs = GameSystem;
sf::Vector2i gs::screen_size = sf::Vector2i{ 1920,1080 };
sf::Vector2f gs::screen_size_f = static_cast<sf::Vector2f>(gs::screen_size);
sf::Vector2f gs::screen_mid = sf::Vector2f{ gs::screen_size_f.x / 2, (gs::screen_size_f.y / 2)};
std::string GameSystem::sprites_path = "../../../../res/sprites/";

int main() {
	sf::RenderWindow window(sf::VideoMode(gs::screen_size.x, gs::screen_size.y), "SFML Test");

	RenderMan::SetWindow(&window);
	SceneManager::init();

	while (window.isOpen()) {
		RenderMan::RenderWindowClear();
		sf::Event event;

		static sf::Clock clock;
		const float dt = clock.restart().asSeconds();

		SceneManager::update(dt);
		EventManager::update(dt);

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

