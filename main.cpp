#include <SFML/Graphics.hpp>
#include "Engine\RenderMan.h"
#include "Engine\SceneMan.hpp"
#include "Engine\Scene.hpp"
#include "Engine\game_system.h"

sf::Vector2i GameSystem::screen_size = sf::Vector2i{ 1000,1000 };
sf::Vector2f GameSystem::screen_size_f = static_cast<sf::Vector2f>( GameSystem::screen_size);

int main() {
	sf::RenderWindow window(sf::VideoMode(GameSystem::screen_size.x, GameSystem::screen_size.y), "SFML Test");

	RenderMan::SetWindow(&window);

	// Should probably remove this render test stuff
	auto circle = std::make_shared<sf::CircleShape>(200.f);
	circle->setFillColor(sf::Color::Green);
	circle->setPosition(0, 0);

	auto pain = std::make_shared<sf::RectangleShape>(sf::Vector2f(300.f, 300.f));
	pain->setFillColor(sf::Color::Yellow);
	pain->setPosition(1000, 0);

	RenderMan::createDrawable(circle, 1);
	RenderMan::createDrawable(pain, 0);

	//RenderMan::RemoveDrawObjByDrawable(pain);

	SceneManager::init();

	while (window.isOpen()) {
		RenderMan::RenderWindowClear();
		sf::Event event;
		pain->setPosition(pain->getPosition().x - 1, 50);

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

