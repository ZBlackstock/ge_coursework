#include "UI_exit_to_mainmenu.hpp"
#include "game_system.h"

using exit = ExitToMainMenu;
using gs = GameSystem;


std::shared_ptr<Button_LoadScene> exit::yes = nullptr;
std::shared_ptr<Button> exit::no = nullptr;

void exit::init() // Need to link to main.cpp
{
	// Create sprite
	RenderMan::create_sprite("exit_to_main_menu", gs::screen_mid, 10);
}

void exit::set_active(bool active)
{
	if (active)
	{
		// Set popup pos to middle
		RenderMan::set_sprite_pos("exit_to_main_menu", gs::screen_mid);

		// Define yes and no buttons
		exit::yes = std::make_shared<Button_LoadScene>
			("yes", sf::Vector2f{ gs::screen_mid.x - 100, gs::screen_mid.y + 50 }, 11);
		exit::no = std::make_shared<Button>
			("no", sf::Vector2f{ gs::screen_mid.x + 100, gs::screen_mid.y + 50 }, 11);
	}
	else if (!active)
	{
		//Set popup pos to off screen
		RenderMan::set_sprite_pos("exit_to_main_menu", sf::Vector2f{ 10000,10000 });

		// Define yes and no buttons
		exit::yes = std::make_shared<Button_LoadScene>
			("yes", sf::Vector2f{ gs::screen_mid.x - 100, gs::screen_mid.y + 50 }, 11);
		exit::no = std::make_shared<Button>
			("no", sf::Vector2f{ gs::screen_mid.x + 100, gs::screen_mid.y + 50 }, 11);
	}

}
