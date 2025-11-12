#pragma once
#include <SFML/Graphics.hpp>


struct DrawObj {
    sf::Drawable* object;
    int layer;
};

class RenderMan {
public:

    void SetWindow(sf::RenderWindow* win);

    void AddDrawable(const DrawObj* newObj);

    DrawObj createDrawable(sf::Drawable* object, int layer);

    void RenderWindowClear();

    void RenderWindow();

private:
    sf::RenderWindow* window = nullptr;
    std::vector<const DrawObj*> drawObjects;
};