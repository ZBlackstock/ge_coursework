#include <SFML/Graphics.hpp>
#include "RenderMan.h"
#include "Game_System.h"

void GameSystem::start(unsigned int width, unsigned int height,
    const std::string& name, const float& time_step)
{
    sf::RenderWindow window(sf::VideoMode({ width, height }), name);
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
                clean();
                return;
            }

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        RenderMan::RenderWindowClear();
        _update(dt);
        _render();
        _sounds();

        sf::sleep(sf::seconds(time_step));
        //Wait for Vsync
        window.display();
    }

    window.close();
    clean();
}

void GameSystem::_update(const float& dt) {
    _active_scene->update(dt);
}