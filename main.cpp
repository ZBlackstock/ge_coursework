#include <SFML/Graphics.hpp>
#include "Engine\RenderMan.h"



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
    
     DrawObj* kys = new DrawObj(renderer.createDrawable(&circle, 0));
    DrawObj* imInPain = new DrawObj(renderer.createDrawable(&pain, 1));

    pain.setPosition(100, 50);
    renderer.RenderWindow();


    renderer.AddDrawable(kys);
    renderer.AddDrawable(imInPain);
    while (window.isOpen()) {
        renderer.RenderWindowClear();
        sf::Event event;
        pain.setPosition(pain.getPosition().x - 1, 50);

        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        renderer.RenderWindow();
    }
    return 0;
}

