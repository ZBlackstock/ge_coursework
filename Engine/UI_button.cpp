#include "UI_button.hpp"
#include "RenderMan.h"
#include <SFML/Graphics.hpp>
#include "game_system.h"
#include <iostream>
#include <string>

using b = Button;
using rm = RenderMan;
using gs = GameSystem;

b::Button(std::string name_in_file, Button above, Button Below, sf::Vector2f location, int sort_layer)
{
	try
	{
		Button b::_above = above;
		Button b::_below = below;

		RenderMan::create_sprite(gs::sprites_path + name_in_file + "_idle", { 10000,10000 }, sort_layer);
		RenderMan::create_sprite(gs::sprites_path + name_in_file + "_highlighted", { 10000,10000 }, sort_layer);
		RenderMan::create_sprite(gs::sprites_path + name_in_file + "_selected", { 10000,10000 }, sort_layer);
		RenderMan::create_sprite(gs::sprites_path + name_in_file + "_disabled", { 10000,10000 }, sort_layer);
	}
	catch
	{
		std::cout << "Could not load button" << std::endl
	}
}
