#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>


struct DrawObj
{
	std::shared_ptr<sf::Drawable> object;
	int layer;
};

// Yo
class RenderMan {
public:


	static std::vector<std::unique_ptr<DrawObj>> drawObjects;

	// @brief gets a pointer of the window to render to.
	// @param win points towards the window currently in use
	static void SetWindow(sf::RenderWindow* win);
	static sf::RenderWindow* GetWindow();
	static void create_sprite(std::string tx_file_path, sf::Vector2f pos, int layer);
	static void set_sprite_pos(std::string name, sf::Vector2f pos);

	/// @brief Creates a DrawObj struct wrapping a drawable and a layer.
	/// @param object Shared Pointer to the SFML drawable object.
	/// @param layer Layer index for rendering order.
	/// @return A DrawObj raw ptr if the caller needs one
	static DrawObj* createDrawable(const std::shared_ptr<sf::Drawable> object, int layer);

	// @brief clears the window pointed to by SetWindow
	static void RenderWindowClear();

	/** @brief loops through all DrawObj pointers in list
	*
	* drawObjects and draws them to the
	*
	*     window pointed to by SetWindow
	*/
	static void RenderWindow();

	/**
	* @brief remove a DrawObj pointer from list
	* @param toRemove is the pointer for the DrawObj to delete
	*/
	static void RemoveDrawObjByDrawable(const std::shared_ptr<sf::Drawable>& drawable);

	/**
	* @brief delete all DrawObj Pointers from list
	*/
	static void RemoveAllDrawObj();

private:
	static sf::RenderWindow* window;
	static std::vector<std::shared_ptr<sf::Texture>> textures;
	static std::map<std::string, std::shared_ptr<sf::Sprite>> sprites;

	/// @brief Adds a unique_ptr to the vector in RenderMan.
	/// @param newObj Pointer to the DrawObj to add.
	static void AddDrawable(std::unique_ptr<DrawObj> newObj);

};