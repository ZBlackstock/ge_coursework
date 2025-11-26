#pragma once
#include <SFML/graphics.hpp>
#include <string>

// All variables here should be static, and initialised in main
class GameSystem
{
public:
	static sf::Vector2i screen_size;
	static sf::Vector2f screen_size_f; // float version, for sprite positioning
	static sf::Vector2f screen_mid; // float version, for sprite positioning
	static std::string sprites_path;
	static sf::Font font;
	static sf::Font font_bold;
	static bool fullscreen;
};