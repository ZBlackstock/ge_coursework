#include "UI_exit_to_mainmenu.hpp"
#include "game_system.h"
#include <iostream>
#include "event_man.hpp"

using popup = ExitToMainMenu;
using gs = GameSystem;

// Need add button navigation and Buton deconstructor
std::shared_ptr<Button_LoadScene> popup::yes = nullptr;
std::shared_ptr<Button> popup::no = nullptr;
std::shared_ptr<bool> popup::_active = std::make_shared<bool>(false);

void popup::init() // Need to link to main.cpp
{
	// Create sprite
	RenderMan::create_sprite("exit_to_main_menu.png", sf::Vector2f{ 10000,10000 }, 10);
	// Define yes and no buttons
	popup::yes = std::make_shared<Button_LoadScene>
		("yes", sf::Vector2f{ gs::screen_mid.x + 100, gs::screen_mid.y + 50 }, 11);
	popup::no = std::make_shared<Button>
		("no", sf::Vector2f{ gs::screen_mid.x - 100, gs::screen_mid.y + 50 }, 11);

	// Set button nav, and positions off screen
	popup::yes.get()->set_offscreen(true);
	popup::no.get()->set_offscreen(true);

	//Set button navigation
	popup::yes.get()->set_left(popup::no);
	popup::yes.get()->set_right(popup::no);

	popup::no.get()->set_left(popup::yes);
	popup::no.get()->set_right(popup::yes);
}

void popup::set_active(bool active)
{
	*popup::_active = active;
	if (active)
	{
		std::cout << "popup active true" << std::endl;

		// Set popup pos to middle
		RenderMan::set_sprite_pos("exit_to_main_menu.png", gs::screen_mid);

		// Set Yes/No to off screen	
		popup::yes.get()->set_offscreen(false);
		popup::no.get()->set_offscreen(false);

		// Set current button
		EventManager::set_current_button(popup::no);
	}
	else if (!active)
	{
		std::cout << "popup active false" << std::endl;

		//Set popup pos to off screen
		RenderMan::set_sprite_pos("exit_to_main_menu.png", sf::Vector2f{ 10000,10000 });

		// Set Yes/No to off screen	
		popup::yes.get()->set_offscreen(true);
		popup::no.get()->set_offscreen(true);

		// Clear current button
		EventManager::clear_current_button();
	}

}

bool popup::get_active()
{
	return *popup::_active;
}
