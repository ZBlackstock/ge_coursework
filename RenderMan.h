#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct DrawObj {
    sf::Drawable* object;
    int layer;
};

class RenderMan {
public:

    void SetWindow(sf::RenderWindow* win);

    void AddDrawable(sf::Drawable* obj, int layer);

    void RenderWindow();

private:
    sf::RenderWindow* window = nullptr;
    std::vector<DrawObj> drawObjects;
};