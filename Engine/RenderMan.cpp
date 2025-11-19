#include <SFML/Graphics.hpp>
#include "RenderMan.h"
//manages render order of drawable pointers

std::vector<std::unique_ptr<DrawObj>> RenderMan::drawObjects{};
sf::RenderWindow* RenderMan::window = nullptr;


void RenderMan::SetWindow(sf::RenderWindow* win)
{
    window = win;
}

void RenderMan::AddDrawable(std::unique_ptr<DrawObj> newObj)
{
    drawObjects.push_back(std::move(newObj));
}


DrawObj* RenderMan::createDrawable(const std::shared_ptr<sf::Drawable> object, int layer)
{
    auto newObj = std::make_unique<DrawObj>(DrawObj{ object, layer });
    DrawObj* rawPtr = newObj.get();  // optional, if you need to keep a raw pointer
    AddDrawable(std::move(newObj));
    return rawPtr;
}

void RenderMan::RenderWindow()
{

    std::sort(drawObjects.begin(), drawObjects.end(),
        [](const auto& a, const auto& b) { return a->layer < b->layer; });

    for (const auto& drawable : drawObjects) {
        window->draw(*drawable->object);
    }
    window->display();
}

void RenderMan::RemoveDrawObjByDrawable(const std::shared_ptr<sf::Drawable>& drawable)
{
    drawObjects.erase(
        std::remove_if(drawObjects.begin(), drawObjects.end(),
            [&drawable](const std::unique_ptr<DrawObj>& drawObj) {
                return drawObj->object == drawable; // shared_ptr == shared_ptr
            }),
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

/*example of how to add image to render man to display 
* this example assumes that an object of renderMan is called renderer
* 
*auto circle = std::make_shared<sf::CircleShape>(200.f);
*renderer.createDrawable(circle, 0); number is for the layer
*
*to delete a specific drawable from the render 
*renderer.RemoveDrawObjByDrawable(circle);
* 
*to delete all the objs from the list
*renderer.RemoveAllDrawObj();
* 
*to render the window
*renderer.RenderWindow();
* 
*to clear the window
*renderer.RenderWindowClear():
*/