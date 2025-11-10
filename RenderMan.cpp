#include <SFML/Graphics.hpp>
#include "RenderMan.h"


    void RenderMan::SetWindow(sf::RenderWindow* win)
    {
        window = win;
    }

    void RenderMan::AddDrawable(sf::Drawable* obj, int layer)
    {
        DrawObj newObj;
        newObj.object = obj;
        newObj.layer = layer;

        drawObjects.push_back(newObj);
    }

    void RenderMan::RenderWindow()
    {
        for (DrawObj& drawable : drawObjects) {
            window->draw(*drawable.object);
            
        }
        window->display();
    }
