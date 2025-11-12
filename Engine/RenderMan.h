#pragma once
#include <SFML/Graphics.hpp>


struct DrawObj
{
    sf::Drawable* object;
    int layer;
};

class RenderMan {
public:

    // @brief gets a pointer of the window to render to.
    // @param win points towards the window currently in use
    void SetWindow(sf::RenderWindow* win);


    /// @brief Adds a drawable object to the render manager.
    /// @param newObj Pointer to the DrawObj to add. RenderMan does not take ownership.
    void AddDrawable(const DrawObj* newObj);


    /// @brief Creates a DrawObj struct wrapping a drawable and a layer.
    /// @param object Pointer to the SFML drawable object.
    /// @param layer Layer index for rendering order.
    /// @return A DrawObj struct containing the drawable and layer info.
    /// for the caller to copy
    DrawObj createDrawable(sf::Drawable* object, int layer);

    // @brief clears the window pointed to by SetWindow
    void RenderWindowClear();

    /** @brief loops through all DrawObj pointers in list
    * 
    * drawObjects and draws them to the 
    * 
    *     window pointed to by SetWindow
    */
    void RenderWindow();

    /**
    * @brief remove a DrawObj pointer from list
    * @param toRemove is the pointer for the DrawObj to delete
    */
    void RemoveDrawObj(const DrawObj* toRemove);

    /**
    * @brief delete all DrawObj Pointers from list
    */
    void RemoveAllDrawObj();

private:
    sf::RenderWindow* window = nullptr;
    std::vector<const DrawObj*> drawObjects;
};