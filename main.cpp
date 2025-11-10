#include <SFML/Graphics.hpp>
#include "RenderMan.h"



int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "SFML Test");

    RenderMan renderer;       
    renderer.SetWindow(&window);

    sf::CircleShape circle(200.f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(0,0);

    sf::RectangleShape pain(sf::Vector2f(300.f,300.f));
    pain.setFillColor(sf::Color::Yellow);
    pain.setPosition(0, 0);

    renderer.AddDrawable(&circle, 0);
    renderer.AddDrawable(&pain, 1);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        renderer.RenderWindow();
    }
    return 0;
}

