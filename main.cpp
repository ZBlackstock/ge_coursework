#include <SFML/Graphics.hpp>
#include "Engine\RenderMan.h"



int main() {
    static constexpr float time_step = 0.017f;  // this is apperantly what you need to make 60fps idk
                                                // thanks leni
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Test");

    

    RenderMan renderer;       
    renderer.SetWindow(&window);

    auto circle = std::make_shared<sf::CircleShape>(200.f);
    circle->setFillColor(sf::Color::Green);
    circle->setPosition(0, 0);

    auto pain = std::make_shared<sf::RectangleShape>(sf::Vector2f(300.f, 300.f));
    pain->setFillColor(sf::Color::Yellow);
    pain->setPosition(1000, 0);

    renderer.createDrawable(circle, 1);
    renderer.createDrawable(pain, 0);


    while (window.isOpen()) {
        renderer.RenderWindowClear();
        sf::Event event;
        pain->setPosition(pain->getPosition().x - 1, 50);

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        renderer.RenderWindow();
    }
    return 0;
}

