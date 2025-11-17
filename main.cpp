#include <SFML/Graphics.hpp>
#include "Engine\RenderMan.h"
#include "Engine\SceneMan.hpp"
#include "Engine\Scene.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Test");

    RenderMan renderer;       
    renderer.SetWindow(&window);

    // Should probably remove this render test stuff
    auto circle = std::make_shared<sf::CircleShape>(200.f);
    circle->setFillColor(sf::Color::Green);
    circle->setPosition(0, 0);

    auto pain = std::make_shared<sf::RectangleShape>(sf::Vector2f(300.f, 300.f));
    pain->setFillColor(sf::Color::Yellow);
    pain->setPosition(1000, 0);

    renderer.createDrawable(circle, 1);
    renderer.createDrawable(pain, 0);

    renderer.RemoveDrawObjByDrawable(pain);

    SceneManager scene_manager;
    scene_manager.init();

    while (window.isOpen()) {
        renderer.RenderWindowClear();
        sf::Event event;
        pain->setPosition(pain->getPosition().x - 1, 50);

        static sf::Clock clock;
        const float dt = clock.restart().asSeconds();

        scene_manager.update(dt);


        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        renderer.RenderWindow();
    }
    return 0;
}

