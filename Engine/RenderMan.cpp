#include <SFML/Graphics.hpp>
#include "RenderMan.h"
//manages render order of drawable pointers

void RenderMan::SetWindow(sf::RenderWindow* win)
{
    window = win;
}

void RenderMan::AddDrawable(const DrawObj* newObj)
{
    drawObjects.push_back(newObj);
}


DrawObj RenderMan::createDrawable(sf::Drawable* object, int layer)
{
    DrawObj newObj;
    newObj.object = object;
    newObj.layer = layer;
    
    return newObj;
}

void RenderMan::RenderWindow()
{

    std::sort(drawObjects.begin(), drawObjects.end(),
        [](const DrawObj* a, const DrawObj* b) { return a->layer < b->layer; });

    for (const DrawObj* drawable : drawObjects) {
        window->draw(*drawable->object);
    }
    window->display();
}

void RenderMan::RemoveDrawObj(const DrawObj* toRemove)
{
    drawObjects.erase(
        std::remove(drawObjects.begin(), drawObjects.end(), toRemove),
        drawObjects.end()
    );
}


void RenderMan::RemoveAllDrawObj() 
{
    drawObjects.clear();
}

void RenderMan::RenderWindowClear()
{
    window->clear();
}